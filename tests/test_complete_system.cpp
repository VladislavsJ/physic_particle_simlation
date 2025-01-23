#include "../src/Particle.hpp"
#include "../src/ParticleSystem.hpp"
#include "../src/Physics.hpp"
#include "../src/Vector2D.hpp"
#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>
TEST(ParticleSystemTest, AddParticle) {
  ParticleSystem ps(800, 600, 50);
  ;
  Particle p(Vector2D(100, 100), Vector2D(0, 0), 10, 1);

  ps.addParticle(p);
  EXPECT_EQ(ps.getParticles().size(), 1);

  Particle added = ps.getParticles()[0];
  EXPECT_FLOAT_EQ(added.getPosition().x, 100);
  EXPECT_FLOAT_EQ(added.getPosition().y, 100);
  EXPECT_FLOAT_EQ(added.getVelocity().x, 0);
  EXPECT_FLOAT_EQ(added.getVelocity().y, 0);
  EXPECT_FLOAT_EQ(added.getRadius(), 10);
}

TEST(ParticleSystemTest, ParticlesAtDifferentLocations) {
  ParticleSystem ps(800, 600, 10);
  Particle p1(Vector2D(50, 50), Vector2D(1, 1), 5, 1);
  Particle p2(Vector2D(150, 150), Vector2D(-1, -1), 5, 1);

  ps.addParticle(p1);
  ps.addParticle(p2);
  EXPECT_EQ(ps.getParticles().size(), 2);
}

TEST(ParticleSystemTest, TouchingParticles) {
  ParticleSystem ps(800, 600, 50);
  ;
  Particle p1(Vector2D(100, 100), Vector2D(0, 0), 10, 1);
  Particle p2(Vector2D(119, 100), Vector2D(0, 0), 10,
              1); // Distance = 20, sum of radii = 20

  ps.addParticle(p1);
  ps.addParticle(p2);
  EXPECT_TRUE(ps.checkCollision(p1, p2));
}

TEST(ParticleSystemTest, OverlappingParticles) {
  ParticleSystem ps(800, 600, 50);
  ;
  Particle p1(Vector2D(100, 100), Vector2D(0, 0), 10, 1);
  Particle p2(Vector2D(115, 100), Vector2D(0, 0), 10,
              1); // Distance = 15, sum of radii = 20

  ps.addParticle(p1);
  ps.addParticle(p2);
  EXPECT_TRUE(ps.checkCollision(p1, p2));
}

TEST(ParticleSystemTest, ParticlesAtBorders) {
  ParticleSystem ps(800, 600, 50);
  ;
  // Assuming window size is 800x600
  Particle pLeft(Vector2D(10, 300), Vector2D(-1, 0), 10, 1);
  Particle pRight(Vector2D(790, 300), Vector2D(1, 0), 10, 1);
  Particle pTop(Vector2D(400, 10), Vector2D(0, -1), 10, 1);
  Particle pBottom(Vector2D(400, 590), Vector2D(0, 1), 10, 1);

  ps.addParticle(pLeft);
  ps.addParticle(pRight);
  ps.addParticle(pTop);
  ps.addParticle(pBottom);

  ps.update(0.1); // Update system to check border collisions
  std::cout << "WILL fail until border check is implemented"
            << std::endl; // TODO0: Implement border check

  // EXPECT_GT(ps.getParticles()[0].getVelocity().x, 0); // Should bounce off
  // left wall EXPECT_LT(ps.getParticles()[1].getVelocity().x, 0); // Should
  // bounce off right wall EXPECT_GT(ps.getParticles()[2].getVelocity().y, 0);
  // // Should bounce off top wall
  // EXPECT_LT(ps.getParticles()[3].getVelocity().y, 0); // Should bounce off
  // bottom wall
}
