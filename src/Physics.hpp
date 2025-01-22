#ifndef PHYSICS_H
#define PHYSICS_H

#include "BorderInfo.hpp"
#include "Grid.hpp"
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
Particle applyCollisionforP1(Particle &p1, Particle &p2 const);
// Maybe possible to change p1 and p2, but for now idk how to write such window
// handler
//  may double the efficiency.
// TODO3: maybe cheack possibilty and implement the function to handle the
// collision between the particles
} // namespace Physics

#endif // PHYSICS_H
