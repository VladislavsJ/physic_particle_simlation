#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"
#include "global_var.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(); 

    void render(const ParticleSystem& particleSystem); // render each particle for each frame
    void clear();// black screen
    void display(); // display the frame


    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow m_window;
};

#endif // RENDERER_H
