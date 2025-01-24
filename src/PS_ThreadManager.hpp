#ifndef PS_THREADMANAGER_HPP
#define PS_THREADMANAGER_HPP

#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>
#include <vector>

#include "Grid.hpp"
#include "Particle.hpp"
#include "global_var.hpp"

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
// possible races, FIXED
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

// Reuse your struct (if needed for per-thread data)
struct ThreadData {
  int startrow;
  int startcoll;
  int thread_id;
};

class PS_ThreadManager {

public:
  // Constructor takes references needed for collision logic
  PS_ThreadManager(Grid &grid, int threadCount);

  ~PS_ThreadManager();

  // Called once at construction
  void ThreadingInit(int thread_count);

  // Called each frame
  void doCollisions();

private:
  void workerLoop(int threadId);

  void applyCollisions(ThreadData &td);

private:
  // References to data from ParticleSystem
  Grid &m_grid;
  int m_totalCells;
  int m_workerCount;

  std::vector<std::thread> m_workers;

  // Per-thread data (start row, col, direction
  std::vector<ThreadData> m_threadData;

  // Variables to keep track of how many cells remain for each thread
  //
  std::vector<int> m_remainingCells;
  std::vector<int> m_bufferRemainingCells;

  // Synchronization
  std::mutex m_remainingCellsMutex;
  std::mutex m_writeToGrid;

  // Condition variables for "start" and "done" signals
  std::condition_variable m_startCV;
  std::condition_variable m_doneCV;
  std::mutex m_startMutex;
  std::mutex m_doneMutex;

  // We use these to coordinate the threads
  bool m_stop;
  std::atomic<int> m_threadsReady;
  std::atomic<int> m_threadsDone;
  bool m_runCollisions;
};

#endif // PS_THREADMANAGER_HPP
