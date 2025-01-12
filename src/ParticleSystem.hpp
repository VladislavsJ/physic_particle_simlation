#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include "Particle.hpp"
#include "global_var.hpp"

class ParticleSystem {
public:
    void addParticle(const Particle& particle);

    // update the particle system for each frame
    void update(float deltaTime); // all physics calculations are done here
    

    // Accessors
    std::vector<Particle>& getParticles();
    const std::vector<Particle>& getParticles() const;

private:
    std::vector<Particle> m_particles;
};

#endif // PARTICLESYSTEM_H
