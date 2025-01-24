#include "ParticleSystem.hpp"
#include "Physics.hpp"
#include "global_var.hpp"
#include <cmath>
#include <future>
#include <omp.h>
#include <thread>
extern GlobalVar &gv;
enum CalcWindowIndex;
ParticleSystem::ParticleSystem(int dispWidth, int dispHeight,
                               int maxParticleSize)
    : m_grid(dispWidth, dispHeight, maxParticleSize) {
  m_particles.reserve(10000);
  ThreadingInit(11, m_grid);
}

void ParticleSystem::addParticle(const Particle &particle) {

  m_particles.push_back(particle);

  // Then we add a pointer into the grid:
  Particle *pPtr = &m_particles.back();
  m_grid.addParticle(pPtr);
  // TODO0: check this, does it updates or no  m_grid.updateGrid();
  // ofc in next frame, the grid will be updated
}
void ParticleSystem::addParticles(const std::vector<Particle> &particles) {
  for (const auto p : particles) {
    m_particles.push_back(p);
    Particle *pPtr = &m_particles.back();
    m_grid.addParticle(pPtr);
  }
}

void ParticleSystem::update(float deltaTime) {
  for (Particle &p : m_particles) { // WHY AUTO vs Particle is less
                                    // efficient??? 1700 particles vs 2100
    Physics::applyGravity(p, deltaTime);
    p.update(deltaTime);
    Physics::update_border_speed(p);
  }

  m_grid.updateGrid();
  MasterThread(11, m_grid);
}

// may be used in tests
bool ParticleSystem::checkCollision(const Particle &p1,
                                    const Particle &p2) const {
  float r1 = p1.getRadius();
  float r2 = p2.getRadius();
  auto pos1 = p1.getPosition();
  auto pos2 = p2.getPosition();

  auto vect_diff = pos1 - pos2;
  float dist = std::sqrt(vect_diff.x * vect_diff.x + vect_diff.y * vect_diff.y);
  if (dist < r1 + r2) {
    return true;
  }
  return false;
}
int ParticleSystem::getParticleCount() const { return m_particles.size(); }
std::vector<Particle> &ParticleSystem::getParticles() { return m_particles; }

const std::vector<Particle> &ParticleSystem::getParticles() const {
  return m_particles;
}

///////////////////////////
// MULTITHREAD_PARTICLE_UPDATE //
///////////////////////////
// now the idea
// i have many threads,
// they can work in "pairs"
// they have different movement priorty, rigt-left right-left
// if one thread ended its job, it sends the sygnal to the master
// master checks if thread "pair" is still working, if yes
// it divides total cells to compute by two TODO(thread safe check)
//
// and gives this half to free thread
// it is not perfect, but it is a good start
// improves performance as not all cells have same amount of particles
// TODO0: Init thread pool before the loop and use them for each frame.

// TODO3: possible improvement,
// I can count particle amount for each thread, and amount of cells
//  and next frame "shift" the cells,
//  like first and second thead eneded much faster, so they can take 1.2 times
//  more cells and the last thread can take 0.8 times less cells as most of the
//  colissions, particles are on the bottom, gravity...

///////////////////////////
// possible races
///////////////////////////
// if one thread ended its job, it sends the sygnal to the master
// master checks if thread "pair" is still working, if yes
// it divides total cells to compute by two TODO(thread safe check)
//
// in the push_back to the vector, I am not sure if it is a
//
// problem since all threads are working on different cells. possible race to
// get data as near thread may ask for the same data,(should not be a problem)
//(if button for one and top for another is the same cell)
// if start is not from the top left/right corner, it may be a problem
void ParticleSystem::ThreadingInit(int thread_count, Grid &grid) {
  int workerCnt = thread_count - 1;
  // I am worried about non pair thread for now
  // TODO1:
  if (workerCnt % 2 != 0) {
    workerCnt--;
  }
  thread_data.reserve(workerCnt);
  promises.resize(workerCnt);

  futures.reserve(workerCnt);
  for (int i = 0; i < workerCnt; i++) {
    futures.push_back(promises[i].get_future());
  }
  TotalCells = (grid.getRows() - 2) * (grid.getCols() - 2); // real working size
  int spareCells = TotalCells % workerCnt;
  int cells_per_thread = TotalCells / workerCnt;
  RemainingCells.reserve(workerCnt);
  std::vector<std::thread> workers;
  int startcell;
  int startrow;
  int startcoll;
  int threadcells;

  // The number of cells we've assigned so far (from left to right)
  int assignedCells = 0;

  // The "innerCols" is used when mapping linear cell indices to (row, col)
  int innerCols = grid.getCols() - 2;

  for (int i = 0; i < workerCnt; i++) {
    // Distribute any leftover (spare) cells to the first 'spareCells' threads
    int threadcells = cells_per_thread + ((i < spareCells) ? 1 : 0);

    // Decide direction: even i = left->right, odd i = right->left
    bool directionRight = ((i % 2) == 0);

    // Compute which linear cell this thread *starts* from
    int startCellIndex = 0;
    if (directionRight) {
      // Start at the left edge of the chunk
      startCellIndex = assignedCells;
    } else {
      // Start at the right edge of the chunk
      // i.e. the last cell in [assignedCells, assignedCells + threadcells)
      startCellIndex = assignedCells + threadcells - 1;
    }

    // Convert linear index -> row & col
    int startRow = (startCellIndex / innerCols) + 1;
    int startCol = (startCellIndex % innerCols) + 1;

    // Update for the next thread
    assignedCells += threadcells;

    // Book-keeping
    RemainingCells.push_back(threadcells);

    // push_back your thread data
    // If your thread_data structure wants (row, col, direction?), store it
    // If it only stores (row, col, threadIndex), add direction if needed
    thread_data.push_back({startRow, startCol, i /* or direction? */});
  }

  // At this point, you have:
  //  - workerCnt "chunks" of the total inner cells
  //  - The i-th chunk either scanning left->right or right->left
  //  - Correct offsets for skipping the border
}
void ParticleSystem::applyCollisions(ThreadData &ThreadData,
                                     std::vector<int> &RemainingCells,
                                     Grid &grid, std::mutex &CellsToCompute,
                                     std::promise<int> prom) {
  // record time
  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();
  int startrow = ThreadData.startrow;
  int startcoll = ThreadData.startcoll;
  int thread_id = ThreadData.thread_id;
  int remainingcells;
  bool directionRight = (thread_id % 2 == 0);
  CalcWindow calcWindow(m_grid);
  calcWindow.InitWindow(startrow, startcoll, directionRight);
  std::vector<Particle *> ToSend;
  do {
    for (Particle *i : *(calcWindow.getCell(CalcWindowIndex::CENTER))) {
      for (auto &vecPtr : calcWindow.getCalcWindow()) {
        for (Particle *j : *vecPtr) {
          if (i != j) {
            Physics::applyCollisionforP1(*i, *j);
          }
        }
      }
      ToSend.push_back(i); // now I am tryinh to write directly to grid

      // TODO3: efficiency should be checked, as for now master in idle,
      //  but writing may load it
    }
    // prom.set_value(ToSend.size()); // send data to add to the grid to master
    CellsToCompute.lock();
    remainingcells = RemainingCells[thread_id]--;
    CellsToCompute.unlock();
    // TODO1: CHECK INLINING options
    if (remainingcells > 1) {
      calcWindow.Shift();

    } else {
      writeToGrid.lock();
      grid.addParticles(ToSend);
      writeToGrid.unlock();
      break;
    }

  } while (remainingcells > 1);
}
void ParticleSystem::MasterThread(int threadcnt, Grid &grid) {
  BufferRemainingCells = RemainingCells;
  // assuming that ThreadingInit have been done.
  workers.clear();
  int workerCnt = threadcnt - 1;
  for (int i = 0; i < workerCnt; i++) {
    workers.emplace_back(&ParticleSystem::applyCollisions, this,
                         std::ref(thread_data[i]), std::ref(RemainingCells),
                         std::ref(grid), std::ref(CellsToCompute),
                         std::move(promises[i]));
  }

  for (auto &t : workers) {
    t.join();
  }
  RemainingCells = BufferRemainingCells;
}