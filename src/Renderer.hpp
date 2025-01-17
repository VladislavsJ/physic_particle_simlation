#ifndef RENDERER_H
#define RENDERER_H

#include "Graphs_new.hpp"
#include "ParticleSystem.hpp"
#include "global_var.hpp"
#include "graphical_items.hpp"
#include "user_interactions_new.hpp"
#include <SFML/Graphics.hpp>
class Graph;
class Renderer {
public:
  Renderer();
  ~Renderer();

  bool init();

  void render(const ParticleSystem &particleSystem,
              bool clear = false); // render each particle for each frame
  // clear = clear the screen or not, may be useful to show other tables on the
  // screen
  void clear();   // black screen
  void display(); // display the frame

  void render_graph(Graph &graph, bool clear = true); // render the graphs
  // clear = clear the screen or not, may be useful to show other tables on the
  // screen
  void render_graphs(std::vector<Graph> &graphs, bool clear = true);
  void drawLineGraph(const std::vector<float> &data,
                     float maxValue, //// Helper that draws data as a line graph
                     float offsetX, float offsetY, float width, float height,
                     sf::Color color, bool isInteger = false);
  void renderUI(const UserInteractions &
                    ui); // render user interaction interface, buttons, sliders.
  sf::RenderWindow &getWindow();

private:
  sf::RenderWindow m_window;
};

#endif // RENDERER_H
