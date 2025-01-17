#ifndef PHYSICS_H
#define PHYSICS_H

#include "BorderInfo.hpp"
#include "Particle.hpp"
#include "global_var.hpp"
#include <vector>

namespace Physics {

// TODO3: user should be abble to change gravity
extern float CONTRACTION_FORCE;

// Functions
void applyGravity(Particle &p, float deltaTime);
void handleCollisions(std::vector<Particle> &particles);
void check_Borders(Particle p, int fieldSizeX,
                   int fieldSizeY); // check if particle is at the border

void update_border_speed(Particle &p); // change the border if detectet that
// particle is near the border

} // namespace Physics

#endif // PHYSICS_H
