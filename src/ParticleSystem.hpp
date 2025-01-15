#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include "Particle.hpp"
#include "global_var.hpp"

extern GlobalVar &gv;

class ParticleSystem {
public:
    void addParticle(const Particle& particle);

    // update the particle system for each frame
    void update(float deltaTime); // all physics calculations are done here
    
    bool checkCollision(const Particle& p1, const Particle& p2) const;
    void update_border_state();
    // Accessors
    std::vector<Particle>& getParticles();
    const std::vector<Particle>& getParticles() const;
    int getParticleCount() const;
private:
    std::vector<Particle> m_particles;
};

#endif // PARTICLESYSTEM_H
