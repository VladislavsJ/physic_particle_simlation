#include "ParticleSystem.hpp"
#include "Physics.hpp"
#include "global_var.hpp"
#include <cmath>
extern GlobalVar &gv;
void ParticleSystem::addParticle(const Particle &particle) {

  m_particles.push_back(particle);
  m_grid.addParticle(particle);
  m_grid.updateGrid();
}
void ParticleSystem::addParticles(const std::vector<Particle> &particles) {
  m_particles.insert(m_particles.end(), particles.begin(), particles.end());
  m_grid.addParticles(particles);
  m_grid.updateGrid();
}
void ParticleSystem::update(float deltaTime) {
  // 1. Apply gravity to each particle
<<<<<<< HEAD
=======

>>>>>>> 27518d9 (mess, part of the change.  should not be pushed)
  for (auto &p : m_particles) {
    Physics::applyGravity(p, deltaTime);

    // 3. Update positions
    p.update(deltaTime);

    // Handle border collisions
    Physics::update_border_speed(p);
  }

  Physics::handleCollisions(m_particles);
}

void ParticleSystem::update(float deltaTime) {
  CalcWindow calcWindow(m_grid); // for now one thread, one CalcWindow
  calcWindow.InitWindow(
      {0, 0}); // start from the top left corner, there is empty cells
  // around the "rear" borders
  // calcWindow now has 9 cells, 3x3, with the center in the top left corner

  while (calcWindow.Shift()) { //// shift the window , if it is the end, then
                               ///will return false
    for (Particle i : calcWindow.getCell(
             CalcWindowIndex::CENTER)) { // particle i is new Particle copy
      // to avoid rewriting the grid before all particles are updated
      Physics::applyGravity(i, deltaTime);
      i.update(deltaTime);
      Physics::update_border_speed(i);

      for (Particle j : calcWindow.getCalcWindow()) {
        if (i != j) {
          if (checkCollision(i, j)) {
            Physics::applyCollisionforP1(i, j);
          }
        }
      }
      m_grid.addParticle(i);
    }
  }
}
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
