#include "Renderer.hpp"
#include <iostream>

extern GlobalVar &gv;
Renderer::Renderer() {
  // constructor
}

Renderer::~Renderer() {
  // destructor
  // TODO2
}
bool Renderer::init() {
  //  SFML window
  m_window.create(
      sf::VideoMode(gv.getFieldSizeX() + 200, gv.getFieldSizeY() + 50),
      "Particle Simulator"); // +200 for graphs
  if (!m_window.isOpen()) {
    return false;
  }
  return true;
}
void Renderer::render(const ParticleSystem &particleSystem, bool clear) {
  // render each particle for each frame
  if (clear == true) {
    m_window.clear();
  }
  for (auto &p : particleSystem.getParticles()) {
    sf::CircleShape circle(p.getRadius());
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(p.getPosition().x, p.getPosition().y);
    // TODO3: Set color, for different particles
    sf::Color pColor = p.changeColor_Fspeed();
    circle.setFillColor(pColor);
    m_window.draw(circle);
  }
}
void Renderer::clear() { m_window.clear(); }
void Renderer::display() { m_window.display(); }

sf::RenderWindow &Renderer::getWindow() { return m_window; }
void Renderer::render_graph(Graph &graph, bool clear) {
  float valXmin, valXmax, valYmin, valYmax;
  if (clear == true) {
    m_window.clear();
  }
  if (graph.m_valXmin == graph.m_valXmax) { // if graph size is not assgined
                                            // auto scale
    valXmin = graph.findMinValueX();
    valXmax = graph.findMaxValueX();
  } else {
    valXmin = graph.m_valXmin;
    valXmax = graph.m_valXmax;
  }
  if (graph.m_valYmin == graph.m_valYmax) { // if graph size is not assgined
    // auto scale
    valYmin = graph.findMinValueY();
    valYmax = graph.findMaxValueY();
  } else {
    valYmin = graph.m_valYmin;
    valYmax = graph.m_valYmax;
  }
  drawLineGraph(
      /* data = */ graph.m_dataY,
      /* maxValueY = */ valYmax,
      /* offsetX = */ graph.m_graphDrawStartX,
      /* offsetY = */ graph.m_graphDrawStartY,
      /* width   = */ graph.m_graphSizeX,
      /* height  = */ graph.m_graphSizeY,
      /* color   = */ sf::Color::Red);
}
void Renderer::render_graphs(std::vector<Graph> &graphs, bool clear) {
  for (Graph &graph : graphs) {
    render_graph(graph, clear);
  }
}
// Helper that draws data as a line graph
void Renderer::drawLineGraph(const std::vector<float> &data, float maxValue,
                             float offsetX, float offsetY, float width,
                             float height, sf::Color color, bool isInteger) {
  if (data.size() < 2) {
    return; // Not enough points to draw
  }

  // We’ll create a vertex array for lines
  sf::VertexArray lines(sf::LineStrip, data.size());

  // The x step between points
  float step = width / static_cast<float>(data.size() - 1);

  // Map data to [0..height]
  // For frameTime or count, bigger is higher
  // draw "up" inside the window, but SFML’s Y grows downward, so we
  // invert
  for (size_t i = 0; i < data.size(); i++) {
    float x = offsetX + i * step;
    float y = offsetY + height - (data[i] / maxValue) * height;
    lines[i].position = sf::Vector2f(x, y);
    lines[i].color = color;
  }

  m_window.draw(lines);
}

void Renderer::renderUI(const UserInteractions &ui) {
  for (auto &slider : ui.getSliders()) {
    slider.renderSlidebar(m_window);
  }
  for (auto &btnPair : ui.getButtons_Interact()) {
    btnPair.first.renderButton(m_window);
  }
}
