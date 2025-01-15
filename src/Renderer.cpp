#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer() {
    // constructor
}

Renderer::~Renderer() {
    // destructor 
    //TODO2
}
bool Renderer::init() {
    //  SFML window
    m_window.create(sf::VideoMode(800, 600), "Particle Simulator");
    if (!m_window.isOpen()) {
        return false;
    }
    return true;
}
void Renderer::render(const ParticleSystem& particleSystem) {
    // render each particle for each frame
    m_window.clear();
    for (auto& p : particleSystem.getParticles()) {
        sf::CircleShape circle(p.getRadius());
            circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setPosition(p.getPosition().x,p.getPosition().y);
        //TODO3: Set color, for different particles

        m_window.draw(circle);
    }
}
void Renderer::clear() {
    // black screen
    m_window.clear();
}
void Renderer::display() {
    // display the frame
    m_window.display();
}
sf::RenderWindow& Renderer::getWindow() {
    return m_window;
}

