#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include "Particle.hpp"
#include "global_var.hpp"

namespace Physics {

    //TODO3: Gravity should be changed at runtime for the user
    extern float CONTRACTION_FORCE;

    // Functions
    void applyGravity(Particle& p, float deltaTime);
    //void applyChargeForces(std::vector<Particle>& particles, float deltaTime);
    void handleCollisions(std::vector<Particle>& particles);

}

#endif // PHYSICS_H
