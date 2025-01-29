#include "PS_ThreadManager.hpp"
#include "Physics.hpp"
#include <cmath>

extern GlobalVar &gv;
PS_ThreadManager::PS_ThreadManager(Grid &grid, int thread_count)
    : m_grid(grid), m_threadCnt(thread_count),
      m_workerCount(thread_count - 1), // master thread
      m_threadsReady(0), m_threadsDone(0), m_runCollisions(false),
      m_stop(false) {
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
  m_threadPaths.resize(m_workerCount);
  m_threadPaths_buf.resize(m_workerCount);
  std::vector<std::thread> workers;
  int startcell;
  int startrow;
  int startcoll;
  int threadcells;

  int assignedCells = 0;

  int innerCols = m_grid.getCols() - 2;
  CalcWindow calcWindow(m_grid);
  for (int i = 0; i < m_workerCount; i++) {
    int threadcells = cells_per_thread + ((i < spareCells) ? 1 : 0);

    // Decide direction: even i = left->right, odd i = right->left
    bool directionRight = ((i % 2) == 0);

    // Compute which linear cell this thread *starts* from
    int startCellIndex = 0;
    // Start at the left edge of the chunk
    startCellIndex = assignedCells;

    // Convert linear index -> row & col
    int endRow = ((startCellIndex + threadcells - 1) / innerCols) + 1;
    int endColl = ((startCellIndex + threadcells - 1) % innerCols) + 1;
    int startRow = (startCellIndex / innerCols) + 1;
    int startCol = (startCellIndex % innerCols) + 1;
    // Update for the next thread
    assignedCells += threadcells;
    m_threadData[i].endRow = endRow;

    m_threadData[i].endColl = endColl;

    m_threadData[i].startRow = startRow;
    m_threadData[i].startColl = startCol;

    m_threadData[i].thread_id = i;
    m_threadPaths[i] = calcWindow.getCalcPath(i, m_threadData[i], threadcells);
    m_threadPaths_buf[i] = m_threadPaths[i];
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
      m_threadPaths[i] = m_threadPaths_buf[i];
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
  int startrow = td.startRow;
  int startcoll = td.startColl;
  int cellComputed = 0;
  bool directionRight = (thread_id % 2 == 0); // can be done in the init
  CalcWindow calcWindow(m_grid);
  calcWindow.InitWindow(td, directionRight);
  std::vector<Particle *> ToSend;
  while (true) { // remainingcells <=1 break the loop
    // 1) Check how many cells remain for this thread to process
    int remainingcells = 0;
    {
      std::lock_guard<std::mutex> lock(m_remainingCellsMutex);
      m_remainingCells[thread_id]--;
      remainingcells = m_remainingCells[thread_id];
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
    if (remainingcells > 0) {
      cellComputed++;
      calcWindow.Shift();
    } // else { // check if any thread has more than 2 cells
      //  DEBUG
    /*

      int slowestThread = thread_id;
      int slowestTCells = 0;
      for (int thread = 0; thread < m_workerCount; thread++) {
        if (m_remainingCells[thread] > slowestTCells &&
            m_remainingCells[thread] > 2) {
          slowestThread = thread;
          slowestTCells = m_remainingCells[thread];
        }
      }
      if (slowestTCells > 4) {
        // bigger half goes to the slowest thread, smaller half goes to the
        // current thread
        std::pair<int, int> pos;
        {
          std::lock_guard<std::mutex> lock(m_remainingCellsMutex);
          m_remainingCells[slowestThread] = (slowestTCells + 1) / 2;
          m_remainingCells[thread_id] =
              (slowestTCells / 2); // -1 as I will init window in this if()
          for (int i = 0; i < slowestTCells / 2; i++) {
            // split m_remainingCells[slowestThread] into two parts
            m_threadPaths[thread_id].push_back(
                m_threadPaths[slowestThread].front());
            m_threadPaths[slowestThread].erase(
                m_threadPaths[slowestThread].begin());
          }
          //  std::vector<std::vector<std::pair<int, int>>> m_threadPaths;

          pos = m_threadPaths[thread_id].back();
        }

        calcWindow.InitWindow(pos.first, pos.second);

      }
*/
    else {
      m_writeToGrid.lock();
      m_grid.addParticles(ToSend);
      // std::cout << "DEBUG: " << ToSend.size() << std::endl;
      m_writeToGrid.unlock();
      if (ToSend.size() > 2) {
        // std::cout << "DEBUG: " << ToSend.size() << std::endl;
      }
      // std::cout << "thread" << thread_id
      //           << " cells computed = " << cellComputed << std::endl;
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
    // time

    applyCollisions(m_threadData[threadId]);

    // std::cout << "thread" << threadId << " time  = "
    //           << std::chrono::duration_cast<std::chrono::microseconds>(end -
    //                                                                    begin)
    //                  .count()
    //           << std::endl;
    {
      // Done barrier
      std::unique_lock<std::mutex> lock(m_doneMutex);
      m_threadsDone++;

      // std::cout << "thread" << threadId << " time  = " << time <<
      // std::endl;

      if (m_threadsDone == m_workerCount) {
        // Last worker to finish collisions. Wake main:
        m_doneCV.notify_one();
      }
    }
  }
}

// get each thread cell numbers
//  I did mistake with the "snake logic", and its much harder to start to go
//  from left and from right,
// as they may have crossing cells, Soooo, to "save" the idea about pair cell
// work,
//  I need to write into array all the cells, and then compare, if they are
//  the same, just shift, do not compute the collisions
//  TODO3: check efficiency, as all this is needed just to
//  change the size
/*




                                                   }
                                                   */