#include "PS_ThreadManager.hpp"
#include "Physics.hpp"
#include <cmath>

extern GlobalVar &gv;
PS_ThreadManager::PS_ThreadManager(Grid &grid, int thread_count)
    : m_grid(grid), m_threadCnt(thread_count),
      m_workerCount(thread_count - 1), // master thread
      m_threadsReady(0), m_threadsDone(0), m_runCollisions(false) {
  ThreadingInit(thread_count);
}
void PS_ThreadManager::ThreadingInit(int thread_count) {
  // I am worried about non pair thread for now
  // TODO1:
  if (m_workerCount % 2 != 0) {
    m_workerCount--;
  }
  m_threadData.resize(m_workerCount);

  m_totalCells =
      (m_grid.getRows() - 2) * (m_grid.getCols() - 2); // real working size
  int spareCells = m_totalCells % m_workerCount;
  int cells_per_thread = m_totalCells / m_workerCount;
  m_remainingCells.resize(m_workerCount);
  m_bufferRemainingCells.resize(m_workerCount);
  std::vector<std::thread> workers;
  int startcell;
  int startrow;
  int startcoll;
  int threadcells;

  int assignedCells = 0;

  int innerCols = m_grid.getCols() - 2;

  for (int i = 0; i < m_workerCount; i++) {
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

    m_threadData[i].startrow = startRow;
    m_threadData[i].startcoll = startCol;
    m_threadData[i].thread_id = i;

    m_remainingCells[i] = threadcells;
    m_bufferRemainingCells[i] = threadcells;
  }
  // thread creation
  //  They will wait on a condition variable for each frame's collision pass
  for (int i = 0; i < m_workerCount; i++) {
    m_workers.emplace_back(&PS_ThreadManager::workerLoop, this, i);
  }
}

void PS_ThreadManager::doCollisions() {
  {
    int cnt = 0;
    std::unique_lock<std::mutex> lock(m_startMutex);
    for (int i = 0; i < m_workerCount; i++) {
      m_remainingCells[i] = m_bufferRemainingCells[i];
    }
    m_threadsReady = 0;
    m_threadsDone = 0;
    m_runCollisions = true; // signal that we want collisions to run now
  }

  // Wake up all worker threads
  m_startCV.notify_all();

  // Wait until all threads are done
  {
    std::unique_lock<std::mutex> lock(m_doneMutex);
    m_doneCV.wait(lock, [this] { return m_threadsDone == m_workerCount; });
  }
}

void PS_ThreadManager::applyCollisions(ThreadData &td) {
  int thread_id = td.thread_id;
  int startrow = td.startrow;
  int startcoll = td.startcoll;
  bool directionRight = (thread_id % 2 == 0); // can be done in the init
  CalcWindow calcWindow(m_grid);
  calcWindow.InitWindow(startrow, startcoll, directionRight);
  std::vector<Particle *> ToSend;
  while (true) { // remainingcells <=1 break the loop
    // 1) Check how many cells remain for this thread to process
    int remainingcells = 0;
    {
      std::lock_guard<std::mutex> lock(m_remainingCellsMutex);
      remainingcells = m_remainingCells[thread_id];
      if (remainingcells > 0) {
        m_remainingCells[thread_id]--;
      }
    }

    // Collision logic
    for (Particle *i : *(calcWindow.getCell(CalcWindowIndex::CENTER))) {
      for (auto &vecPtr : calcWindow.getCalcWindow()) {
        for (Particle *j : *vecPtr) {
          if (i != j) {
            Physics::applyCollisionforP1(*i, *j);
          }
        }
      }
      ToSend.push_back(i);
    }
    // 2) If no cells remain, break the loop
    if (remainingcells > 1) {
      calcWindow.Shift();
    } else {
      m_writeToGrid.lock();
      m_grid.addParticles(ToSend);
      m_writeToGrid.unlock();
      break;
    }
  }
}

void PS_ThreadManager::workerLoop(int threadId) {
  while (true) {
    {

      std::unique_lock<std::mutex> lock(m_startMutex);

      //  Wait until main calls doCollisions() -> m_runCollisions = true
      //  or until we want to stop everything (m_stop == true).
      m_startCV.wait(lock, [this] { return (m_runCollisions || m_stop); });
      m_threadsReady++;
      if (m_threadsReady == m_workerCount) {
        // Last one to become ready: wake everyone so we all pass the barrier
        m_runCollisions = false;
        m_barrierCV.notify_all();

      } else {
        // Wait for the last thread to do notify_all
        m_barrierCV.wait(lock,
                         [this] { return m_threadsReady == m_workerCount; });
      }
    }

    // Actual collisions:
    applyCollisions(m_threadData[threadId]);

    {
      // Done barrier
      std::unique_lock<std::mutex> lock(m_doneMutex);
      m_threadsDone++;
      if (m_threadsDone == m_workerCount) {
        // Last worker to finish collisions. Wake main:
        m_doneCV.notify_one();
      }
    }
  }
}
