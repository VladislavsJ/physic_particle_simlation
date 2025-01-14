#include "Physics.hpp"
#include <cmath>
GlobalVar &gv = GlobalVar::getInstance();
namespace Physics {

    float GRAVITY = gv.getGravity();
    //float CONTRACTION_FORCE // TODO2: Implement this
    //particles should contract to each other if they have different charge
    void applyGravity(Particle& p, float deltaTime) {
        // If there's no charge or if we decide charge doesn't negate gravity,
        // we just add downward acceleration (gravity).
        auto vel = p.getVelocity();
        vel.y += GRAVITY * deltaTime;
        p.setVelocity(vel);
    }
    void handleCollisions(std::vector<Particle>& particles) {
        // Iterate through all unique pairs of particles
        for (size_t i = 0; i < particles.size(); ++i) {
            for(size_t j = i + 1; j < particles.size(); ++j) {
                auto& p1 = particles[i];
                auto& p2 = particles[j];
                float r1 = p1.getRadius();
                float r2 = p2.getRadius();
                auto pos1 = p1.getPosition();
                auto pos2 = p2.getPosition();
                
                // Compute the vector difference 
                auto vect_diff = pos1 - pos2;
                float dist = std::sqrt(vect_diff.x * vect_diff.x + vect_diff.y * vect_diff.y);
                

                if (dist < (r1 + r2)) {
                    // Collision detected
                    // Avoid  zero
                    if (dist == 0.0f) {
                        //  direction to separate the particles, just 1.0f in x direction
                        vect_diff = {1.0f, 0.0f};
                        dist = 1.0f;
                    }

                    float overlap = (r1 + r2) - dist;

                    float nx = vect_diff.x / dist;
                    float ny = vect_diff.y / dist;

                    float m1 = p1.getMass();
                    float m2 = p2.getMass();
                    float totalMass = m1 + m2;

                    float ratio1 = m2 / totalMass;
                    float ratio2 = m1 / totalMass;

                    // Update positions to resolve the collision
                    // it mostly needed if particles are assigned to the same position
                    // otherways direction will be changed thanks to the velocity change.
                    pos1.x += nx * overlap * ratio1;
                    pos1.y += ny * overlap * ratio1;
                    pos2.x -= nx * overlap * ratio2;
                    pos2.y -= ny * overlap * ratio2;

                    p1.setPosition(pos1);
                    p2.setPosition(pos2);

                    // --- Collision Response: Adjust Velocities ---
                    
                    auto vel1 = p1.getVelocity();
                    auto vel2 = p2.getVelocity();

                    float rvx = vel1.x - vel2.x;
                    float rvy = vel1.y - vel2.y;

                    float velAlongNormal = rvx * nx + rvy * ny;

                    // Do not resolve if velocities are separating
                    if (velAlongNormal > 0.001) // floating point tolerance
                        continue;

                    // coliision elasticity
                    float restitution = (p1.getElasticity()+p2.getElasticity())/2; // TODO3: Implement elasticity for each particle

                    float impulseScalar = -(1 + restitution) * velAlongNormal;
                    impulseScalar /= (1/m1) + (1/m2);

                    float impulseX = impulseScalar * nx;
                    float impulseY = impulseScalar * ny;
                    //if other particle are on the bottom, then top particle get 80% of impulse and bottom 20%
                    if (p1.border.isBorderSet(BORDER_BOTTOM)) {
                        if (pos1.y > pos2.y ) { // p1 is on top
                        //TODO0: no check for x

                            vel1.x = -(impulseX / m1)*0.2;//just numbers from my head
                            //TODO1:
                            vel1.y = -(impulseY / m1) * 0.2;
                            vel2.x = -(impulseX / m2) * 1.8;
                            vel2.y = -(impulseY / m2) * 1.8;
                            p1.setVelocity(vel1);
                            p2.setVelocity(vel2);
                            continue;
                        } else {
                            
                        }
                    }
                    vel1.x += (impulseX / m1);
                    vel1.y += (impulseY / m1);
                    vel2.x -= (impulseX / m2);
                    vel2.y -= (impulseY / m2);

                    p1.setVelocity(vel1);
                    p2.setVelocity(vel2);
                }
            }
        }

        // TODO: Handle collisions with walls or other boundaries if applicable
    }
    
    
}