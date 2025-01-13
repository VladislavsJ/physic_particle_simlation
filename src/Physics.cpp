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
        // The particles should not overlap.
        // The particles should not pass through each other.
        // The particles should not pass through the walls of the field.
        // The particles should not pass through the
        for (size_t i = 0; i < particles.size(); ++i) {
            for(size_t j = i + 1; j < particles.size(); ++j) {
                auto& p1 = particles[i];
                auto& p2 = particles[j];
                float r1 = p1.getRadius();
                float r2 = p2.getRadius();
                auto pos1 = p1.getPosition();
                auto pos2 = p2.getPosition();

                auto vect_diff = pos1 - pos2;
                float dist = std::sqrt(vect_diff.x * vect_diff.x + vect_diff.y * vect_diff.y);
                if (dist < r1 + r2) {
                    // Collision detected, distance is less than the sum of the radius
                    // Move the particles apart, 

                    Vector2D normal(vect_diff.x / dist, vect_diff.y / dist);
                    //shift the particles apart for the half of the overlap
                    p1.getPosition() = pos1 + normal * ((r1 + r2 - dist) / 2);
                    p2.getPosition() = pos2 - normal * ((r1 + r2 - dist) / 2);

                    //TODO3: Implement the collision response, velocity change if needed

                }

            }

}
    }
    
    
}