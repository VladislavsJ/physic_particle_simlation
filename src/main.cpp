#include <SFML/Graphics.hpp>
#include <iostream>
#include "ParticleSystem.hpp"
#include "Renderer.hpp"

int main() {
    Renderer renderer;
    if (!renderer.init()) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return 1;
    }
    ParticleSystem particleSystem;// all particles are here
    particleSystem.addParticle(Particle(Vector2D(100, 100), Vector2D(0, 0), 10, 1));
    particleSystem.addParticle(Particle(Vector2D(200, 200), Vector2D(0, 0), 10, 1));
    particleSystem.addParticle(Particle(Vector2D(300, 300), Vector2D(0, 0), 10, 1));
    particleSystem.addParticle(Particle(Vector2D(400, 400), Vector2D(0, 0), 10, 1));
    particleSystem.addParticle(Particle(Vector2D(500, 500), Vector2D(0, 0), 10, 1));
    
    sf::Clock clock;
    while (renderer.getWindow().isOpen()) {
        sf::Time deltaTime = clock.restart();
        sf::Event event;
        while (renderer.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                renderer.getWindow().close();
            }
        }
        particleSystem.update(deltaTime.asSeconds());
        renderer.render(particleSystem);
        renderer.display();
    }


}