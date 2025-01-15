#ifndef PHYSICS_H
#define PHYSICS_H

#include "BorderInfo.hpp"
#include "Particle.hpp"
#include "global_var.hpp"
#include <vector>

namespace Physics {

// TODO3: Gravity should be changed at runtime for the user
extern float CONTRACTION_FORCE;

// Functions
void applyGravity(Particle &p, float deltaTime);
// void applyChargeForces(std::vector<Particle>& particles, float deltaTime);
void handleCollisions(std::vector<Particle> &particles);
void check_Borders(Particle p, int fieldSizeX,
                   int fieldSizeY); // check if particle is at the border
// now it checks which border, left right, top or bottom

} // namespace Physics

#endif // PHYSICS_H
