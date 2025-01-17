#include "Graphs_new.hpp"
#include "ParticleSystem.hpp"
#include "Renderer.hpp"
#include "user_interactions_new.hpp" // (Optional) Ensure this reflects your actual header name for UserInteractions
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

// TODO LIST , to comment the ideas/thoughts
// TODO0: High risk, must be fixed and thoroughly checked before use.
// TODO1: Important functionality, but the system may operate without it.
// TODO2: Ideas for optimization and enhancements; important but not critical.
// TODO3: Future considerations and potential improvements.
extern GlobalVar &gv;

int main() {
  Renderer renderer;
  if (!renderer.init()) {
    std::cerr << "Failed to initialize renderer" << std::endl;
    return 1;
  }
  // std::vector<Graph> &graphs(2); // can't visualize the graphs, in the while
  // loop below, should be fixed
  //  now vector is not used.
  Graph graphFPS;
  Graph graphParticleCnt;

  // two graphs to show FPS and particle count
  if (!graphFPS.init(gv.getFieldSizeX() /*inStartX*/, 50 /*inStartY*/,
                     180 /*inSizeX*/, 180 /*inSizeY*/)) {
    std::cerr << "Failed to initialize graph FPS" << std::endl;
    return 1;
  }
  // graphs.push_back(graphFPS);
  if (!graphParticleCnt.init(gv.getFieldSizeX(), 200, 180, 180)) {
    std::cerr << "Failed to initialize graph Particle Count" << std::endl;
    return 1;
  }
  // graphs.push_back(graphParticleCnt);

  // 1) Instantiate UserInteractions
  UserInteractions ui;
  // Create ParticleSystem
  ParticleSystem particleSystem;
  // Test particles
  particleSystem.addParticle(
      Particle(Vector2D(300, 400), Vector2D(0, 0), 25, 1));
  particleSystem.addParticle(
      Particle(Vector2D(300, 450), Vector2D(0, 0), 30, 1));

  // Setup timing, idea is to hold constant frame rate, while possible and CPU
  // are abble to do so

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
      if (frameDuration.count() > 0.016f) { // totals FPS < 60FPS
        std::cout << "frame time is too high, max particle count is"
                  << std::endl;
        std::cout << particleSystem.getParticleCount() << std::endl;
      }
    }

    // Limit frame rate to 60 fps
    if (frameDuration < FRAME_TIME) {
      frameDuration = FRAME_TIME;
    }

    // test: inject new particles, to see how the system behaves
    if (cnt++ % 1 == 0 && cnt < 10000 && (cnt % 200) < 170) {
      particleSystem.addParticle(
          Particle(Vector2D(100, 100), Vector2D(400, 0), 3, 1));
      if (cnt % 250 == 1) {
        particleSystem.addParticle(
            Particle(Vector2D(40, 80), Vector2D(545, 138), 25, 1));
      }
    }

    particleSystem.update(
        frameDuration.count()); // update particle system, frame duration is
                                // passed to update the system
    // to calculate the new position of the particles

    // Render everything
    renderer.clear();
    renderer.render(
        particleSystem,
        false); // false means not to clear the screen before rendering

    renderer.render_graph(graphFPS, false);
    renderer.render_graph(graphParticleCnt, false);
    renderer.renderUI(ui);
    renderer.display();

    // Update graphs every 10 frames,
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

    // Sleep if frame rendered faster than 60 fps
    if (frameDuration < FRAME_TIME) {
      sf::sleep(sf::seconds((FRAME_TIME - frameDuration).count()));
    }
  }

  return 0;
}
