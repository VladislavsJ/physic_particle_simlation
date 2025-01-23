#include "Physics.hpp"
#include <bit>
#include <cmath>
#include <cstring> // For std::memcpy

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

// Approximate inverse square root using bit manipulation (C++20)
// Safe inverse square root approximation
// OFC I took it from the internet
inline float fastInvSqrt(float x) {
  uint32_t i;
  ::memcpy(&i, &x, sizeof(float));
  i = 0x5f3759df - (i >> 1);
  float y;
  ::memcpy(&y, &i, sizeof(float));
  y = y * (1.5f - 0.5f * x * y * y);
  return y;
}
constexpr float POSITION_ADJUSTMENT =
    0.03f; // I just like it, simulation is bit different
// I would call is Viscosity, but it is not ofc

void applyCollisionforP1(Particle &p1, const Particle &p2) {
  // Cache properties to minimize access overhead
  // compare to getters, public acces gives +-5% speedup
  float r1 = p1.m_radius;
  float r2 = p2.m_radius;
  float px1 = p1.m_position.x;
  float py1 = p1.m_position.y;
  float px2 = p2.m_position.x;
  float py2 = p2.m_position.y;

  // Compute vector difference and distance squared
  float dx = px1 - px2;
  float dy = py1 - py2;
  float distSq = dx * dx + dy * dy;
  float radiusSum = r1 + r2;
  float radiusSumSq = radiusSum * radiusSum;

  // Check for collision
  if (distSq >= radiusSumSq)
    return;
  // Compute distance using fast inverse sqrt, as I don't need to be super
  // precize,
  // TODO3: should be possible to avoid it at all, if store the variables
  // differently, (already precomputed)
  float invDist = fastInvSqrt(distSq);
  float dist = 1.0f / invDist;

  // Handle zero or near-zero distance to avoid division by zero
  if (dist < 1e-6f) {
    dx = 1.0f;
    dy = 0.0f;
    dist = 1.0f;
  } else {
    dx *= invDist;
    dy *= invDist;
  }

  float overlap = radiusSum - dist;

  // Mass ratio
  float m1 = p1.m_mass;
  float m2 = p2.m_mass;
  float totalMass = m1 + m2;
  float ratio1 = m2 / totalMass;

  p1.m_position.x += dx * overlap * ratio1 + POSITION_ADJUSTMENT;
  p1.m_position.y += dy * overlap * ratio1 + POSITION_ADJUSTMENT;
  float rvx = p1.m_velocity.x - p2.m_velocity.x;
  float rvy = p1.m_velocity.y - p2.m_velocity.y;

  // Velocity along the normal
  float velAlongNormal = rvx * dx + rvy * dy;

  // Do not resolve if velocities are separating
  if (velAlongNormal > 0.01f)
    return;

  // Average elasticity
  float restitution = 0.5f * (p1.m_elasticity + p2.m_elasticity);

  // Impulse scalar
  float impulse = -(1.0f + restitution) * velAlongNormal;
  impulse /= (1.0f / m1) + (1.0f / m2);

  // Apply impulse to p1's velocity
  p1.m_velocity.x += (impulse * dx) / m1;
  p1.m_velocity.y += (impulse * dy) / m1;
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