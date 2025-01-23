#include "ParticleSystem.hpp"
#include "Physics.hpp"
#include "global_var.hpp"
#include <cmath>
#include <omp.h>

extern GlobalVar &gv;
enum CalcWindowIndex;
ParticleSystem::ParticleSystem(int dispWidth, int dispHeight,
                               int maxParticleSize)
    : m_grid(dispWidth, dispHeight, maxParticleSize) {
  m_particles.reserve(10000);
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
  for (Particle &p :
       m_particles) { // WHY AUTO is less efficient??? 1700 particles vs 2100
    Physics::applyGravity(p, deltaTime);
    p.update(deltaTime);
    Physics::update_border_speed(p);
  }
  m_grid.updateGrid();
  CalcWindow calcWindow(m_grid); // for now one thread, one CalcWindow
  calcWindow.InitWindow(1, 1);
  // start from the top left corner, there is empty cells
  // 1:1 because 0:0 is "dummy" grid, to calculate borders particles
  int cnt = 0;
  int partcnt = 0;

  do {
    for (Particle *i : *(calcWindow.getCell(CalcWindowIndex::CENTER))) {
      // 1) Update position/velocity

      /* simulation is not the same if this is inside or outside the loop
            Physics::applyGravity(*i, deltaTime);
            i->update(deltaTime);
            Physics::update_border_speed(*i);
        */
      // 2) Collisions
      for (auto &vecPtr : calcWindow.getCalcWindow()) {
        for (Particle *j : *vecPtr) {
          if (i != j) {
            Physics::applyCollisionforP1(*i, *j);
          }
        }
      }
      partcnt++;
      // std::cout << "partcnt: " << partcnt << std::endl;
      m_grid.addParticle(i);
    }
  } while (calcWindow.Shift());
  // std::cout << "partcnt: " << partcnt << std::endl;
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
