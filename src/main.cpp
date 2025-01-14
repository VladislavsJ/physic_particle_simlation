#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "ParticleSystem.hpp"
#include "Renderer.hpp"
//TODO LIST
//TODO0: high risk, should be fixed, checked before use
// TODO1: Important functionality, but may work without it
// TODO2, Ideas for optimization, and important stuff, but not necessary
// TOOD3, just ideas for the future

int main() {
    Renderer renderer;
    if (!renderer.init()) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return 1;
    }
    ParticleSystem particleSystem;// all particles are here
    particleSystem.addParticle(Particle(Vector2D(100, 100), Vector2D(0, 0),10,1));
    particleSystem.addParticle(Particle(Vector2D(200, 200), Vector2D(0, 0), 10, 1));
    particleSystem.addParticle(Particle(Vector2D(300, 300), Vector2D(0, 0), 10, 1));
    particleSystem.addParticle(Particle(Vector2D(400, 400), Vector2D(0, 0), 10, 1));
    particleSystem.addParticle(Particle(Vector2D(500, 200), Vector2D(0, 0), 15 ,1));
    
    sf::Clock clock;
    const float FPS = 60.0f; // Constant for 60 frames per second
    // if frame time is less than 1/60, sleep for the remaining time
    // if frame time is more than 1/60, do nothing
    std::chrono::duration<float> FRAME_TIME = std::chrono::duration<double>(1.0 / FPS);
std::chrono::duration<float> frameDuration;
while (renderer.getWindow().isOpen()) {
        auto frameStartTime = std::chrono::high_resolution_clock::now();
    sf::Event event;

    while (renderer.getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            renderer.getWindow().close();
        }
    }

    if (frameDuration < FRAME_TIME){
        frameDuration = FRAME_TIME;
    }
    particleSystem.update(frameDuration.count());// TODO0: check
    particleSystem.update_border_state();
    renderer.render(particleSystem);

    renderer.display();
    auto frameEndTime = std::chrono::high_resolution_clock::now();
    frameDuration = frameEndTime - frameStartTime;
    if (frameDuration < FRAME_TIME)
        sf::sleep(sf::seconds((FRAME_TIME - frameDuration).count()));
     

}


}