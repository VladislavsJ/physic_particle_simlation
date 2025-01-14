#include "ParticleSystem.hpp"
#include "Physics.hpp"
#include "global_var.hpp"
#include <cmath>
extern GlobalVar &gv;
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
void ParticleSystem::update_border_state() {
    for (auto& p : m_particles) {
        p.border.update_border_state(p.getPosition(), gv.getFieldSizeX(), gv.getFieldSizeY());
        if (p.border.isAnyBorderSet()) {
            p.limit_coordinates(gv.getFieldSizeX(), gv.getFieldSizeY());
            //TODO2: different border handling
            if (p.border.isBorderSet(BORDER_BOTTOM)) { //touched
               // p.setVelocity(Vector2D(0,0));
            }
        }




    }
}

bool ParticleSystem::checkCollision(const Particle& p1, const Particle& p2) const {
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

std::vector<Particle>& ParticleSystem::getParticles() {
    return m_particles;
}

const std::vector<Particle>& ParticleSystem::getParticles() const {
    return m_particles;
}

