
#include "Grid.h"
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>
#include <vector>

class ParticleSystem {
public:
  ParticleSystem();
  ~ParticleSystem();
  void ThreadingInit(int thread_count, Grid &grid);
  void update(float deltaTime);
  void MasterThread(int threadcnt, Grid &grid);

private:
  void applyCollisions(/* parameters */);

  std::vector<std::thread> workers;
  std::vector<std::promise<void>> promises;
  std::vector<std::future<void>> futures;
  std::mutex m_cvMutex;
  std::condition_variable m_cv;
  bool m_frameReady = false;
  bool m_stopThreads = false;
  int workerCnt;
  // Other member variables...
};

ParticleSystem::ParticleSystem() {
  // Constructor implementation...
}

ParticleSystem::~ParticleSystem() {
  {
    std::lock_guard<std::mutex> lock(m_cvMutex);
    m_stopThreads = true;
    m_frameReady = true;
  }
  m_cv.notify_all();
  for (auto &t : workers) {
    if (t.joinable())
      t.join();
  }
}

void ParticleSystem::ThreadingInit(int thread_count, Grid &grid) {
  workerCnt = thread_count - 1;
  // ...existing code where thread_data, promises, etc. are set up...

  // Create fixed worker threads once:
  for (int i = 0; i < workerCnt; i++) {
    workers.emplace_back([this, i, &grid]() {
      while (true) {
        std::unique_lock<std::mutex> lk(m_cvMutex);
        m_cv.wait(lk, [this] { return m_frameReady || m_stopThreads; });
        if (m_stopThreads)
          break;
        lk.unlock();
        // Do collision work for this thread
        applyCollisions(/* parameters */);
      }
    });
  }
}

void ParticleSystem::update(float deltaTime) {
  // ...existing code...
  m_grid.updateGrid();

  // Instead of creating threads here each time, just set frameReady and notify:
  {
    std::lock_guard<std::mutex> lock(m_cvMutex);
    m_frameReady = true;
  }
  m_cv.notify_all();

  // Optionally wait for workers to finish or use some other sync if needed
  for (auto &f : futures) {
    f.wait();
  }

  {
    std::lock_guard<std::mutex> lock(m_cvMutex);
    m_frameReady = false;
  }
}

void ParticleSystem::MasterThread(int threadcnt, Grid &grid) {
  // Remove per-frame thread creation:
  // ...existing code...
  // workers.clear(); // <-- remove
  // ...existing code that emplace_back threads... // <-- remove
  // Instead, these collisions are handled by the fixed threads signaled in
  // update()
}

void ParticleSystem::applyCollisions(/* parameters */) {
  // Implementation of collision handling...
}