#include "Physics.hpp"
#include <cmath>
GlobalVar &gv = GlobalVar::getInstance();
namespace Physics {

float GRAVITY = gv.getGravity();
// float CONTRACTION_FORCE // TODO3: Implement this
// particles should contract to each other if they have different charge

void applyGravity(Particle &p, float deltaTime) {
  // add downward acceleration (gravity). TOOD3: make gravity direction
  // changeable
  auto vel = p.getVelocity();
  vel.y += GRAVITY * deltaTime;
  p.setVelocity(vel);
}
void applyCollisionforP1(Particle &p1, Particle const &p2) {
  float r1 = p1.getRadius();
  float r2 = p2.getRadius();
  auto pos1 = p1.getPosition();
  auto pos2 = p2.getPosition();

  // Compute the vector difference
  auto vect_diff = pos1 - pos2;
  float dist = vect_diff.x * vect_diff.x + vect_diff.y * vect_diff.y;

  if (dist < (r1 + r2) * (r1 + r2)) {
    // Collision detected
    // Avoid  zero
    dist = std::sqrt(dist);
    if (dist == 0.0f) {

      //  direction to separate the particles, just 1.0 in x direction
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

    // Update positions
    pos1.x += nx * overlap * ratio1;
    pos1.y += ny * overlap * ratio1;

    p1.setPosition(pos1);

    // Collision Response, Adjust Velocities

    auto vel1 = p1.getVelocity();
    auto vel2 = p2.getVelocity();

    float rvx = vel1.x - vel2.x;
    float rvy = vel1.y - vel2.y;

    float velAlongNormal = rvx * nx + rvy * ny;

    // Do not resolve if velocities are separating
    if (velAlongNormal > 0.001) // floating point tolerance
      return;

    // coliision elasticity
    float restitution = (p1.getElasticity() + p2.getElasticity()) /
                        2; // TODO3: Implement elasticity for each particle

    float impulseScalar = -(1 + restitution) * velAlongNormal;
    impulseScalar /= (1 / m1) + (1 / m2);

    float impulseX = impulseScalar * nx;
    float impulseY = impulseScalar * ny;
    // if other particle are on the bottom, then top particle get 80% of
    // impulse and bottom 20%, why? just because I want it
    vel1.x += (impulseX / m1);
    vel1.y += (impulseY / m1);
    p1.setVelocity(vel1);
  }
}

void update_border_speed(Particle &p) {
  p.border.update_border_state(p.getPosition(), p.getRadius(),
                               gv.getFieldSizeX(), gv.getFieldSizeY());
  if (p.border.isAnyBorderSet()) {
    p.limitCoordinates(gv.getFieldSizeX(), gv.getFieldSizeY());
    // TODO2: different border handling
    if (p.border.isBorderSet(
            BORDER_BOTTOM)) { // touched BORDER_BOTTOM, set velocity backwards
                              // *0.5, just because I want it,
      // assuming that groud absorb more energy
      if (p.getVelocity().y > 0) {
        p.setVelocity(Vector2D(p.getVelocity().x, (-p.getVelocity().y) * 0.9));

        if (p.getVelocity().y > -2) { // if y is really small, stop it
          p.setVelocity(Vector2D(p.getVelocity().x,
                                 0)); // if particle is too slow, stop it
        }
      }
    }
    if (p.border.isBorderSet(BORDER_TOP)) {
      if (p.getVelocity().y < 0) {
        p.setVelocity(Vector2D(p.getVelocity().x, (-p.getVelocity().y) * 0.9));
      }
    }
    if (p.border.isBorderSet(BORDER_LEFT)) {
      if (p.getVelocity().x < 0) {
        p.setVelocity(
            Vector2D((-1 * p.getVelocity().x) * 0.9, p.getVelocity().y));
      }
    } else if (p.border.isBorderSet(BORDER_RIGHT)) {
      if (p.getVelocity().x > 0) {
        p.setVelocity(
            Vector2D((-1 * p.getVelocity().x) * 0.9, p.getVelocity().y));
      }
    }
  }
}
} // namespace Physics
// namespace Physics