#include "Graphs_new.hpp"
#include "ParticleSystem.hpp"
#include "Renderer.hpp"
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
  //   float inValXMin = 0, float inValYMin = 0,
  if (!graphFPS.init(gv.getFieldSizeX(), 50, 180, 180)) {
    std::cerr << "Failed to initialize graph FPS" << std::endl;
    return 1;
  };

  if (!graphParticleCnt.init(gv.getFieldSizeX(), 200, 180, 180)) {
    std::cerr << "Failed to initialize graph Particle Count" << std::endl;
    return 1;
  }

  ParticleSystem particleSystem;

  //  test particles
  particleSystem.addParticle(
      Particle(Vector2D(300, 400), Vector2D(0, 0), 1, 1));
  particleSystem.addParticle(
      Particle(Vector2D(300, 499), Vector2D(0, 0), 15, 1));

  sf::Clock clock;
  const float FPS = 60.0f;
  std::chrono::duration<float> FRAME_TIME =
      std::chrono::duration<double>(1.0 / FPS);
  std::chrono::duration<float> frameDuration;
  auto frameEndTime = std::chrono::high_resolution_clock::now();
  int cnt = 0;
  while (renderer.getWindow().isOpen()) {
    auto frameStartTime = std::chrono::high_resolution_clock::now();

    // Handle events for main window
    sf::Event event;
    while (renderer.getWindow().pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        renderer.getWindow().close();
      }
    }

    if (cnt % 10 ==
        0) { // check frame time every 10 frames, to check the performance
      std::cout << "frame time: " << frameDuration.count() << std::endl;

      if (frameDuration.count() > 0.016) {
        std::cout << "frame time is too high, max particle count is"
                  << std::endl;
        std::cout << particleSystem.getParticleCount() << std::endl;
      }
    }

    // to save CPU resources, frame rate is limited to 60 fps
    if (frameDuration < FRAME_TIME) {
      frameDuration = FRAME_TIME;
    }

    if (cnt++ % 1 == 0 && cnt < 30000 && cnt % 200 < 100) {
      particleSystem.addParticle(
          Particle(Vector2D(300, 400), Vector2D(200, 0), 3, 1));
    }

    // Update particle system
    particleSystem.update(frameDuration.count());
    particleSystem.update_border_state();

    // Render in the main window
    renderer.render(particleSystem, true);
    renderer.render_graph(graphFPS, false);
    renderer.render_graph(graphParticleCnt, false);
    renderer.display();

    //---
    //  Update Graphs data and render:
    //---
    if (cnt % 10 == 0) {

      graphFPS.updateData(
          cnt, std::chrono::duration_cast<std::chrono::duration<float>>(
                   std::chrono::high_resolution_clock::now() - frameStartTime)
                   .count());
      graphParticleCnt.updateData(cnt, particleSystem.getParticleCount());
    }

    frameEndTime = std::chrono::high_resolution_clock::now();
    frameDuration = frameEndTime - frameStartTime;
    // Sleep if we’re still under the desired frame time
    if (frameDuration < FRAME_TIME) {
      sf::sleep(sf::seconds((FRAME_TIME - frameDuration).count()));
    }
  }

  return 0;
}
