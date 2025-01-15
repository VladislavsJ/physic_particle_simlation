#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"
#include "global_var.hpp"
#include "Graphs_new.hpp"
class Graph;
class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(); 

    void render(const ParticleSystem& particleSystem, bool clear=true); // render each particle for each frame
    // clear = clear the screen or not, may be useful to show other tables on the screen
    void clear();// black screen
    void display(); // display the frame

    void render_graph(Graph& graph, bool clear = true); // render the graphs
    // clear = clear the screen or not, may be useful to show other tables on the screen
    void drawLineGraph(const std::vector<float>& data, float maxValue, //// Helper that draws data as a line graph
                       float offsetX, float offsetY, float width, float height, 
                       sf::Color color, bool isInteger = false);

    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow m_window;
};

#endif // RENDERER_H
