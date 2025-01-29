#include "ParticleSystem.hpp"
#include "PS_ThreadManager.hpp"
#include "Physics.hpp"
#include "global_var.hpp"
#include <cmath>
#include <future>
#include <omp.h>
#include <thread>
extern GlobalVar &gv;
enum CalcWindowIndex;
class PS_ThreadManager;
ParticleSystem::ParticleSystem(int dispWidth, int dispHeight,
                               int maxParticleSize)
    : m_grid(dispWidth, dispHeight, maxParticleSize), m_threadManager(nullptr) {
  m_particles.reserve(
      10000); // TODO2: MAX_PARTICLES, cant be changed during the runtime
  // if >10 000 reallocation happens and bye bye program
  m_threadManager = new PS_ThreadManager(m_grid, /*threadCount=*/11);
  // one is master
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
  // 1) Apply physics (gravity, border collision, etc.)
  // #pragma omp parallel for threadNum(10)
  // no speedup from for loop
  // time
  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();
  for (Particle &p : m_particles) {
    Physics::applyGravity(p, deltaTime);
    p.update(deltaTime);
    Physics::update_border_speed(p);
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  std::chrono::steady_clock::time_point begin1 =
      std::chrono::steady_clock::now();
  // Perform collisions using the thread manager
  if (m_threadManager) {
    m_threadManager->doCollisions();
  }
  //   std::chrono::steady_clock::time_point end1 =
  //   std::chrono::steady_clock::now(); std::chrono::steady_clock::time_point
  //   begin3 =
  //       std::chrono::steady_clock::now();
  m_grid.updateGrid();
  //   std::chrono::steady_clock::time_point end3 =
  //   std::chrono::steady_clock::now(); std::cout << "Physics time  = "
  //             << std::chrono::duration_cast<std::chrono::microseconds>(end -
  //                                                                      begin)
  //                    .count()
  //             << "us" << std::endl;
  //   std::cout << "Collisions time  = "
  //             << std::chrono::duration_cast<std::chrono::microseconds>(end1 -
  //                                                                      begin1)
  //                    .count()
  //             << "us" << std::endl;
  //   std::cout << "Grid update time  = "
  //             << std::chrono::duration_cast<std::chrono::microseconds>(end3 -
  //                                                                      begin3)
  //                    .count()
  //             << "us" << std::endl;
  //
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
