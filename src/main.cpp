#include "Graphs_new.hpp"
#include "ParticleSystem.hpp"
#include "Renderer.hpp"
#include "user_interactions_new.hpp" // (Optional) Ensure this reflects your actual header name for UserInteractions
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

extern GlobalVar &gv;

int main() {
  Renderer renderer;
  if (!renderer.init()) {
    std::cerr << "Failed to initialize renderer" << std::endl;
    return 1;
  }

  Graph graphFPS;
  Graph graphParticleCnt;
  // int inStartX, int inStartY, int inSizeX, int inSizeY,
  // float inValXMin = 0, float inValYMin = 0,
  if (!graphFPS.init(gv.getFieldSizeX(), 50, 180, 180)) {
    std::cerr << "Failed to initialize graph FPS" << std::endl;
    return 1;
  }

  if (!graphParticleCnt.init(gv.getFieldSizeX(), 200, 180, 180)) {
    std::cerr << "Failed to initialize graph Particle Count" << std::endl;
    return 1;
  }

  // 1) Instantiate UserInteractions
  UserInteractions ui;

  // 2) NEW: Initialize Sliders/Buttons in the UI
  ui.initUI(); // <---- ADDED

  // Create ParticleSystem
  ParticleSystem particleSystem;
  // Test particles
  particleSystem.addParticle(
      Particle(Vector2D(300, 400), Vector2D(0, 0), 25, 1));
  particleSystem.addParticle(
      Particle(Vector2D(300, 450), Vector2D(0, 0), 30, 1));

  // Setup timing / FPS
  sf::Clock clock;
  const float FPS = 60.0f;
  std::chrono::duration<float> FRAME_TIME =
      std::chrono::duration<float>(1.0f / FPS);
  std::chrono::duration<float> frameDuration;
  auto frameEndTime = std::chrono::high_resolution_clock::now();

  int cnt = 0;
  while (renderer.getWindow().isOpen()) {
    auto frameStartTime = std::chrono::high_resolution_clock::now();

    // Handle window events
    sf::Event event;
    while (renderer.getWindow().pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        renderer.getWindow().close();
      }
      ui.handleEvent(event, renderer.getWindow(), particleSystem);
    }

    // Periodic logging for frame duration
    if (cnt % 10 == 0) {
      std::cout << "frame time: " << frameDuration.count() << std::endl;
      if (frameDuration.count() > 0.016f) {
        std::cout << "frame time is too high, max particle count is"
                  << std::endl;
        std::cout << particleSystem.getParticleCount() << std::endl;
      }
    }

    // Limit frame rate to 60 fps
    if (frameDuration < FRAME_TIME) {
      frameDuration = FRAME_TIME;
    }

    // Example: inject new particles up to 1000 frames, every 200 frames for 100
    // ticks
    if (cnt++ % 1 == 0 && cnt < 1000 && (cnt % 200) < 100) {
      particleSystem.addParticle(
          Particle(Vector2D(300, 200), Vector2D(400, 0), 3, 1));
    }

    // Update particle system
    particleSystem.update(frameDuration.count());

    // Render everything
    renderer.render(particleSystem, true);
    renderer.render_graph(graphFPS, false);
    renderer.render_graph(graphParticleCnt, false);
    renderer.renderUI(ui);
    renderer.display();

    // Update graphs every 10 frames
    if (cnt % 10 == 0) {
      graphFPS.updateData(
          cnt, std::chrono::duration_cast<std::chrono::duration<float>>(
                   std::chrono::high_resolution_clock::now() - frameStartTime)
                   .count());
      graphParticleCnt.updateData(cnt, particleSystem.getParticleCount());
    }

    // Measure frame time
    frameEndTime = std::chrono::high_resolution_clock::now();
    frameDuration = frameEndTime - frameStartTime;

    // Sleep if still under desired frame time
    if (frameDuration < FRAME_TIME) {
      sf::sleep(sf::seconds((FRAME_TIME - frameDuration).count()));
    }
  }

  return 0;
}
