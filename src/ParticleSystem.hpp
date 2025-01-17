#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle.hpp"
#include "global_var.hpp"
#include <vector>

extern GlobalVar &gv;

class ParticleSystem {
public:
  void addParticle(const Particle &particle);
  void addParticles(const std::vector<Particle> &particles);
  // update the particle system for each frame
  void update(float deltaTime); // all physics calculations are done here

  bool checkCollision(const Particle &p1, const Particle &p2) const;
  // Getters
  std::vector<Particle> &getParticles();
  const std::vector<Particle> &getParticles() const;
  int getParticleCount() const;

private:
  std::vector<Particle> m_particles;
};
void addParticles(const std::vector<Particle> &particles);

#endif
