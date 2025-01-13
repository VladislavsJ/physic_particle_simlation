#include "ParticleSystem.hpp"
#include "Physics.hpp"

void ParticleSystem::addParticle(const Particle& particle) {
    m_particles.push_back(particle);
}

void ParticleSystem::update(float deltaTime) {
    // 1. Apply gravity to each particle
    for (auto& p : m_particles) {
        Physics::applyGravity(p, deltaTime);
    }

    // 3. Update positions
    for (auto& p : m_particles) {
        p.update(deltaTime);
    }

    // 4. Handle collisions
    Physics::handleCollisions(m_particles);

    
}

std::vector<Particle>& ParticleSystem::getParticles() {
    return m_particles;
}

const std::vector<Particle>& ParticleSystem::getParticles() const {
    return m_particles;
}

