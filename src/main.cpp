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

    particleSystem.addParticle(Particle(Vector2D(300, 400), Vector2D(0, 0), 1, 1));
    particleSystem.addParticle(Particle(Vector2D(300, 499), Vector2D(0, 0), 15, 1));

    sf::Clock clock;
    const float FPS = 60.0f; // Constant for 60 frames per second
    // if frame time is less than 1/60, sleep for the remaining time
    // if frame time is more than 1/60, do nothing
    std::chrono::duration<float> FRAME_TIME = std::chrono::duration<double>(1.0 / FPS);
std::chrono::duration<float> frameDuration;
int cnt = 0; 
while (renderer.getWindow().isOpen()) {
        auto frameStartTime = std::chrono::high_resolution_clock::now();
    sf::Event event;

    while (renderer.getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            renderer.getWindow().close();
        }
    }
    cnt++;
    if (cnt % 10 == 0) {
        particleSystem.addParticle(Particle(Vector2D(100, 100), Vector2D(100, 0), 2, 1));
    }
    if (frameDuration < FRAME_TIME){
        frameDuration = FRAME_TIME;
    }
    std::cout << cnt;
            

    if (cnt++ % 3 == 0 && cnt < 300) {
        
        //particleSystem.addParticle(Particle(Vector2D(100, 100), Vector2D(100, 0), 10, 1));
    }
    
    particleSystem.update_border_state();
    particleSystem.update(frameDuration.count());// TODO0: check
    renderer.render(particleSystem);

    renderer.display();
    auto frameEndTime = std::chrono::high_resolution_clock::now();
    frameDuration = frameEndTime - frameStartTime;
    if (frameDuration < FRAME_TIME)
        sf::sleep(sf::seconds((FRAME_TIME - frameDuration).count()));
     

}


}