#include "PS_ThreadManager.hpp"
#include "Physics.hpp"
#include <cmath>

extern GlobalVar &gv;

PS_ThreadManager::PS_ThreadManager(Grid &grid, int threadCount)
    : m_grid(grid), m_stop(false), m_threadsReady(0), m_threadsDone(0),
      m_runCollisions(false) {
  // We will initialize the threads here
  ThreadingInit(threadCount);
}

PS_ThreadManager::~PS_ThreadManager() {
  // Signal all threads to stop
  {
    std::unique_lock<std::mutex> lock(m_startMutex);
    m_stop = true;
    m_runCollisions = true; // just to unblock them
  }
  m_startCV.notify_all();

  // Join all threads
  for (auto &t : m_workers) {
    if (t.joinable()) {
      t.join();
    }
  }
}

// This basically replaces the old MasterThread + ThreadingInit done each frame.
// Instead, we do it once.
void PS_ThreadManager::ThreadingInit(int thread_count) {
  // This is the total number of threads we want (including  the main thread).
  //  (thread_count - 1) worker threads.

  m_workerCount = thread_count - 1;
  // TODO3: NOT sure if not pair thread will work
  if (m_workerCount % 2 != 0) {
    m_workerCount--;
  }

  // We compute total cells (excluding border)
  m_totalCells = (m_grid.getRows() - 2) * (m_grid.getCols() - 2);

  //  thread data
  m_threadData.resize(m_workerCount);
  m_remainingCells.resize(m_workerCount);
  m_bufferRemainingCells.resize(m_workerCount);

  // logic for dividing cells among the worker threads
  int spareCells = m_totalCells % m_workerCount;
  int cellsPerThread = m_totalCells / m_workerCount;
  int assignedCells = 0;
  int innerCols = m_grid.getCols() - 2;

  for (int i = 0; i < m_workerCount; i++) {
    int threadcells =
        cellsPerThread +
        ((i < spareCells) ? 1 : 0); // distribute any leftover cells
    bool directionRight =
        ((i % 2) == 0); // snake style, left->right, right->left
    int startCellIndex =
        (directionRight) ? assignedCells : (assignedCells + threadcells - 1);

    int startRow = (startCellIndex / innerCols) +
                   1; // 1-based indexing, as 0 is "dummy cell"
    int startCol = (startCellIndex % innerCols) +
                   1; // 1-based indexing as 0 is "dummy cell"

    m_threadData[i].startrow = startRow;
    m_threadData[i].startcoll = startCol;
    m_threadData[i].thread_id = i;

    assignedCells += threadcells;
    m_remainingCells[i] = threadcells;
    m_bufferRemainingCells[i] = threadcells;
  }

  for (int i = 0; i < m_workerCount; i++) {
    m_workers.emplace_back(&PS_ThreadManager::workerLoop, this, i);
  }
}

//
void PS_ThreadManager::doCollisions() {
  // Reset some counters for this "frame"
  // We'll copy back the buffer so each thread has the fresh remaining cell
  // count
  {
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

// The old "applyCollisions" code, adapted for an infinite worker loop
void PS_ThreadManager::applyCollisions(ThreadData &td) {
  int thread_id = td.thread_id;
  int startrow = td.startrow;
  int startcoll = td.startcoll;
  bool directionRight = (thread_id % 2 == 0);

  // The local "window" struct from your code
  CalcWindow calcWindow(m_grid);
  calcWindow.InitWindow(startrow, startcoll, directionRight);

  std::vector<Particle *> toSend;

  while (true) {
    int remainingcells = 0;

    // 1) Check how many cells remain for this thread to process
    {
      std::lock_guard<std::mutex> lock(m_remainingCellsMutex);
      remainingcells = m_remainingCells[thread_id];
      if (remainingcells > 0) {
        m_remainingCells[thread_id]--;
      }
    }

    // 2) If no cells left, break
    if (remainingcells <= 0) {
      // push all local updates back to the grid if needed
      // (here we do it once at the end)
      {
        std::lock_guard<std::mutex> lock(m_writeToGrid);
        m_grid.addParticles(toSend);
      }
      break;
    }

    // 3) Perform collisions for the current cell
    //    (This is your old collision logic)
    for (Particle *i : *(calcWindow.getCell(CalcWindowIndex::CENTER))) {
      for (auto &vecPtr : calcWindow.getCalcWindow()) {
        for (Particle *j : *vecPtr) {
          if (i != j) {
            Physics::applyCollisionforP1(*i, *j);
          }
        }
      }
      // accumulate toSend
      toSend.push_back(i);
    }

    // 4) Move to the next cell
    calcWindow.Shift();
  }
}

// The main function each thread runs in a loop
void PS_ThreadManager::workerLoop(int threadId) {
  // Local reference
  ThreadData td = m_threadData[threadId];

  while (true) {
    // Wait until we're told to do collisions or to stop
    {
      std::unique_lock<std::mutex> lock(m_startMutex);
      // Increase 'ready' counter once we get here
      m_threadsReady++;

      // Wait for a new "run" signal or a "stop" signal
      m_startCV.wait(lock, [this] { return (m_runCollisions || m_stop); });

      if (m_stop) {
        // Time to exit the thread permanently
        return;
      }
    }

    // Actually do collisions
    applyCollisions(td);

    // We're done. Increase "done" counter and possibly notify main
    {
      std::unique_lock<std::mutex> lock(m_doneMutex);
      m_threadsDone++;
      if (m_threadsDone == m_workerCount) {
        // All workers done => notify main
        m_doneCV.notify_one();
      }
    }
  } // while(true)
}
