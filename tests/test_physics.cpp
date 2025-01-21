#include "../src/Particle.hpp"
#include "../src/Physics.hpp"
#include "../src/global_var.hpp"
#include <cmath> // for std::sqrt
#include <gtest/gtest.h>

// Helper function to compare floating-point values
static constexpr float EPSILON = 1e-4f;

TEST(PhysicsTests, ApplyGravity) {
  // Get the global instance and set a known gravity
  GlobalVar &gv = GlobalVar::getInstance();
  gv.setGravity(9.81f);

  // Create a particle at rest
  // Particle constructor: Particle(Vector2D pos, Vector2D vel, float radius,
  // int type, float charge, float density)
  Particle p({0.0f, 0.0f}, {0.0f, 0.0f}, /*radius=*/1.0f, /*type=*/0,
             /*charge=*/1.0f, /*density=*/1.0f);

  p.setDensity(1.0f);
  p.setElasticity(1.0f);

  float deltaTime = 1.2f;
  Physics::applyGravity(p, deltaTime);

  // We expect velocity.y to be 9.81 after 1 second
  auto finalVel = p.getVelocity();
  EXPECT_NEAR(finalVel.y, 9.81f, EPSILON)
      << "Velocity.y should match gravity * deltaTime (9.81 for deltaTime=1)";
}
/* TODO0: , can't check if logic is correct

TEST(PhysicsTests, HandleCollisions)
{
    // Create two overlapping particles to force a collision
    // Note the distance is 1.5, and each has radius=1.0 => sum of radii=2.0 =>
overlap Particle p1({100.0f, 800.0f}, {0.0f, 500.0f}, 1.0f, 0, 0.0f, 1.0f);
//laying on the down border Particle p2({100.0f, 791.0f}, {0.0f, 0.0f}, 1.0f, 0,
0.0f, 1.0f);

    p1.setMass(1.0f);
    p1.setElasticity(0.8f);

    p1.border.update_border_state(p1.getPosition(), 800, 800);
    p2.border.update_border_state(p2.getPosition(), 800, 800);
    p2.setMass(1.0f);
    p2.setElasticity(0.8f);

    std::vector<Particle> particles {p1, p2};

    // Run the collision handler
    Physics::handleCollisions(particles);

    // Grab updated particles after collision
    auto& p1Updated = particles[0];
    auto& p2Updated = particles[1];

    // Check the distance between centers
    auto distX = p1Updated.getPosition().x - p2Updated.getPosition().x;
    auto distY = p1Updated.getPosition().y - p2Updated.getPosition().y;
    float distanceAfter = std::sqrt(distX * distX + distY * distY);

    // They should be at least radius1 + radius2 apart
    float minDist = p1Updated.getRadius() + p2Updated.getRadius();
    EXPECT_GE(distanceAfter, minDist - EPSILON)
        << "Particles should be at least their radii apart after collision
resolution.";

    // Check that they gained some velocity (i.e. not zero if the collision was
elastic) auto v1 = p1Updated.getVelocity(); auto v2 = p2Updated.getVelocity();

    float speed1 = std::sqrt(v1.x * v1.x + v1.y * v1.y);
    float speed2 = std::sqrt(v2.x * v2.x + v2.y * v2.y);

    EXPECT_GT(speed1, 0.0f) << "First particle should gain some velocity after
collision."; EXPECT_GT(speed2, 0.0f) << "Second particle should gain some
velocity after collision.";
}
*/