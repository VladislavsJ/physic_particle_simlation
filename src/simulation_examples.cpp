#include "simulation_examples.hpp"
#include "ParticleSystem.hpp"

// Example macro-based test definition (if your framework uses something like
// this):
void make_test1(ParticleSystem &particleSystem) {

  // Parameters for the block of particles
  int rows = 30; // 20 x 40 = 800
  int cols = 50;
  float spacing = 7.0f; // Distance between particle centers
  float startX = 300.0f - (cols * spacing) /
                              2.0f; // Center block horizontally around x=300
  float startY = 100.0f;            // Position the block in the upper area

  // Create the block of ~800 particles
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      float x = startX + j * spacing;
      float y = startY + i * spacing;
      // Particle(radius=5, type=1, charge=0, density=1)
      particleSystem.addParticle(
          Particle(Vector2D(x, y), Vector2D(0, 0), // No initial velocity
                   4.0f,                           // Smaller radius
                   1,                              // Type
                   0.0f,                           // Charge
                   1.0f)                           // Density
      );
    }
  }
}