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
  // We'll draw "up" inside the window, but SFML’s Y grows downward, so we
  // invert
  for (size_t i = 0; i < data.size(); i++) {
    float x = offsetX + i * step;
    float y = offsetY + height - (data[i] / maxValue) * height;
    lines[i].position = sf::Vector2f(x, y);
    lines[i].color = color;
  }

  m_window.draw(lines);

  // Optionally, draw some text (requires loading a font, etc.)
  // For brevity, this snippet doesn't do font drawing.

  // Could also draw axes if you like, etc.
}
void Renderer::renderUI(const UserInteractions &ui) {
  int drawing_Y_pos = 400; // 2 graphs before. 400 is the starting point

  // 1) Draw an icon for AddParticles (yellow rectangle)
  // positon on writing time is 520,420
  sf::RectangleShape addParticlesIcon(sf::Vector2f(32.f, 32.f));
  addParticlesIcon.setFillColor(sf::Color::Yellow);
  addParticlesIcon.setPosition(gv.getFieldSizeX() + 20.f,
                               drawing_Y_pos += 20.f);
  m_window.draw(addParticlesIcon);

  // Size slider background
  // (420,440)
  sf::RectangleShape sizeSliderBG(sf::Vector2f(180.f, 20.0f));
  sizeSliderBG.setFillColor(sf::Color(100, 100, 100));
  sizeSliderBG.setPosition(gv.getFieldSizeX() + 20.f, drawing_Y_pos += 20);
  m_window.draw(sizeSliderBG);

  // Size slider “knob”

  float sizeT =
      (ui.getParticleSize() - 1.f) / (50.f - 1.f); // map 1..50 -> 0..1
  float sizeKnobX =
      gv.getFieldSizeX() + 10.f +
      sizeT * 180.f; // variable position, depending on the previous size
  sf::CircleShape sizeKnob(8.f);
  sizeKnob.setFillColor(sf::Color::Red);
  sizeKnob.setOrigin(8.f, 8.f); // so the circle center is the hot-spot
  sizeKnob.setPosition(sizeKnobX, drawing_Y_pos + 10);
  m_window.draw(sizeKnob);

  // Speed slider background
  sf::RectangleShape speedSliderBG(sf::Vector2f(180.f, 20.f));
  speedSliderBG.setFillColor(sf::Color(100, 100, 100));
  speedSliderBG.setPosition(gv.getFieldSizeX() + 10.f, 150.f);
  m_window.draw(speedSliderBG);

  // Speed slider “knob”
  float speedT = ui.getParticleSpeed() / 500.f; // map 0..500 -> 0..1
  float speedKnobX = gv.getFieldSizeX() + 10.f + speedT * 180.f;
  sf::CircleShape speedKnob(8.f);
  speedKnob.setFillColor(sf::Color::Cyan);
  speedKnob.setOrigin(8.f, 8.f);
  speedKnob.setPosition(speedKnobX, 160.f);
  m_window.draw(speedKnob);
}