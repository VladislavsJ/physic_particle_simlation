#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Grid.hpp"
#include "Particle.hpp"
#include "global_var.hpp"
#include <atomic>
#include <cmath>
#include <condition_variable>
#include <future>
#include <mutex>
#include <omp.h>
#include <thread>
#include <vector>
extern GlobalVar &gv;
struct ThreadData {
  int startrow;
  int startcoll;
  int thread_id;
};

class ParticleSystem {
public:
  ParticleSystem(int dispWidth, int dispHeight,
                 int maxParticleSize); // ASK, why does i need it, GRID:grid
                                       // cant be accesed
  void addParticle(const Particle &particle);
  void addParticles(const std::vector<Particle> &particles);
  // update the particle system for each frame
  void update(float deltaTime); // all physics calculations are done here
  bool checkCollision(const Particle &p1, const Particle &p2) const;
  // Getters
  std::vector<Particle> &getParticles();
  const std::vector<Particle> &getParticles() const;
  int getParticleCount() const;
  void MasterThread(int threadcnt, Grid &grid);
  void WorkerThread(int thread_id);
  void ThreadingInit(int thread_count, Grid &grid);
  void applyCollisions(ThreadData &ThreadData, std::vector<int> &RemainingCells,
                       Grid &grid, std::mutex &CellsToCompute,
                       std::promise<int> prom);

public: // needs to be oublic for the threading
  // TODO2: should be better way how to give the data to the other class,

  Grid m_grid;
  // This system owns actual Particle objects in a vector:
  std::vector<Particle> m_particles;

  // threading
  std::vector<std::thread> workers;        // Worker threads
  std::thread master_thread;               // Master thread
  std::vector<int> RemainingCells;         // Cells to compute
  std::vector<int> BufferRemainingCells;   // Cells to compute
  std::mutex writeToGrid;                  // Mutex for writing to the grid
  std::mutex CellsToCompute;               // Mutex for synchronization
  std::vector<std::promise<int>> promises; // Promises for the threads
  std::vector<std::future<int>> futures;   // Futures for the master thread
  std::vector<ThreadData> thread_data;     // Data for the threads
  int workerCnt;                           // Number of worker threads
  int TotalCells;                          // Total cells to compute
private:
};

#endif
