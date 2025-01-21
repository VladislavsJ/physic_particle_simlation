#include "user_interactions_new.hpp"
#include "Particle.hpp" // For creating new Particles
#include "Vector2D.hpp"
#include "global_var.hpp" // Assuming you need gv.getFieldSizeX(), etc.
#include "user_interface.hpp"
#include <iostream>
extern GlobalVar &gv;
enum class InteractionType;
UserInteractions::UserInteractions()
    : m_currentInteractionType(InteractionType::None),
      m_rightClickStart(false) {
  initUI();
}

void UserInteractions::initUI() {
  // Hard-coded creation of UI controls
  m_userInterface.addSlider(Slidebar(180, 20, gv.getFieldSizeX() + 10, 350,
                                     /*max*/ 50, /*min*/ 1));

  m_userInterface.addSlider(Slidebar(180, 20, gv.getFieldSizeX() + 10, 400,
                                     /*max*/ 10, /*min*/ 0));
  //  button that toggles White_Ball InteractionType, just create the particles.
  m_userInterface.addButton(
      switch_button(20, 20, Vector2D(gv.getFieldSizeX() + 10, 430),
                    sf::Color::White, sf::Color::Red),
      InteractionType::White_Ball);
  // Stop button, to stop the simulation
  m_userInterface.addButton(
      switch_button(20, 20, Vector2D(gv.getFieldSizeX() + 10, 460),
                    sf::Color::Red, sf::Color::Green),
      InteractionType::Stop);
}

void UserInteractions::handleEvent(const sf::Event &event,
                                   sf::RenderWindow &window,
                                   ParticleSystem &particleSystem) {
  // Convert the SFML mouse position to world coords
  sf::Vector2f mousePos =
      window.mapPixelToCoords(sf::Mouse::getPosition(window));

  if (event.type == sf::Event::MouseButtonPressed) {

    if (event.mouseButton.button == sf::Mouse::Left) {

      onLeftClick(mousePos, particleSystem);
    } else if (event.mouseButton.button == sf::Mouse::Right) {
      onRightClick(mousePos);
    } else if (event.type == sf::Event::MouseButtonReleased) {

    } else if (event.type == sf::Event::MouseMoved) {
      MouseMoved(mousePos);
    }
  }
}

void UserInteractions::onLeftClick(const sf::Vector2f &mousePos,
                                   ParticleSystem &particleSystem) {
  // Check where click happened
  //  1) Check sliders
  // if (m_userInterface.update_all_items(mousePos))
  ; // if any item exists at mouse position,
  // return true, this one item will be turned on, and others will be turned off
  InteractionType TempType =
      m_userInterface.update_all_items(mousePos); // if any item exists at mouse
                                                  // position, return
                                                  // interaction type
  if (TempType != InteractionType::None) {
    m_currentInteractionType = TempType;
  }
  if (mousePos.x <= gv.getFieldSizeX() && mousePos.y <= gv.getFieldSizeY()) {
    // if the user clicked inside the field(simulation area)
    if (m_rightClickStart) {
      if (m_currentInteractionType == InteractionType::White_Ball) {
        // The user pressed left after a right-click start => create a Particle
        sf::Vector2f speed = mousePos - m_rightClickPosition;
        std::vector<Slidebar> m_sliders = m_userInterface.getSliders();
        float speedScale = m_sliders[1].getCurrentValue(); // second slider
        float radius = m_sliders[0].getCurrentValue();     // first slider
        speed.x *= speedScale;
        speed.y *= speedScale;

        Particle p(Vector2D(m_rightClickPosition.x, m_rightClickPosition.y),
                   Vector2D(speed.x, speed.y),
                   /*radius*/ radius, /*type*/ 1 /* or any param */);

        std::vector<Particle> newParticles{p};
        particleSystem.addParticles(newParticles);
        // m_rightClickStart = false;
      }
      if (m_currentInteractionType == InteractionType::Stop) {
        // wait, stop the simulation(in main), until the user clicks on the
        // field again
      }
    }
  }
}
void UserInteractions::onRightClick(const sf::Vector2f &mousePos) {
  // Possibly store a "start" for making particles
  if (mousePos.x <= gv.getFieldSizeX() && mousePos.y <= gv.getFieldSizeY()) {
    if (!m_rightClickStart) {
      m_rightClickStart = true;
      m_rightClickPosition = mousePos;
    } else {
      // user right-clicked again => cancel or something
      m_rightClickStart = false;
    }
  }
}

void UserInteractions::MouseMoved(const sf::Vector2f &mousePos) {
  // If the user drags on a slider, update the slider's value
  std::vector<Slidebar> m_sliders = m_userInterface.getSliders();
  for (auto &slider : m_sliders) {
    if (slider.PointOnTheSlider(mousePos)) {
      slider.updateSlider(mousePos);
    }
  }
}
InteractionType UserInteractions::getCurrentInteractionType() const {
  return m_currentInteractionType;
}

std::vector<Slidebar> UserInteractions::getSliders() const {
  return m_userInterface.getSliders();
}
std::vector<std::pair<switch_button, InteractionType>>
UserInteractions::getButtons_Interact() const {
  return m_userInterface.getButtons_interaction();
}