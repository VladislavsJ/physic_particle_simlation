#include "Particle.hpp"   // For creating new Particles
#include "global_var.hpp" // Assuming you need gv.getFieldSizeX(), etc.
#include "user_interactions.hpp"
#include <iostream>
extern GlobalVar &gv;
UserInteractions::UserInteractions()
    : m_currentInteractionType(InteractionType::None),
      m_hasRightClickStart(false), m_particleSize(20.0f) // Default slider value
      ,
      m_particleSpeed(100.0f) // Default slider value
      ,
      m_draggingSizeSlider(false), m_draggingSpeedSlider(false) {
} // TODO0: cut one of the sliders
void UserInteractions::UserInteractions_init() {
  sliders.push_back(
      Slidebar(180, 20, gv.getFieldSizeX() + 10, 200, 50, 1)); // particle size
  // sliders.push_back(Slidebar(180, 20, gv.getFieldSizeX() + 10, 250, 500, 0));
  // now speed is calculated from the distance
  buttons.push_back(switch_button(32, 32,
                                  Vector2D(gv.getFieldSizeX() + 10, 250),
                                  sf::Color::Green, sf::Color::Red));
}
void UserInteractions::handleEvent(const sf::Event &event,
                                   sf::RenderWindow &window,
                                   ParticleSystem &particleSystem) {
  // We only do more specific checking if it's a mouse event
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePos = window.mapPixelToCoords(
          sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
    }
    // Check if the click is within the right data panel or in the main
    // field(simulator) area
    if (mousePos.x >= gv.getFieldSizeX()) {
      // The click is in the 200px right panel
      checkIconClick(mousePos);
      checkSliderClick(mousePos);
    } else {
      // The click is in the main field
      onLeftClick(mousePos, particleSystem);
    }
  } else if (event.mouseButton.button ==
             sf::Mouse::Right) { // if right click, then record the position,
    // it will be used for the creation of the particles if pressed left click
    // after it.
    sf::Vector2f mousePos = window.mapPixelToCoords(
        sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
    // Only if in the main field area
    if (mousePos.x < gv.getFieldSizeX()) {
      onRightClick(mousePos);
    }

  } else if (event.type == sf::Event::MouseButtonReleased) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      // Stop dragging the sliders
      m_draggingSizeSlider = false;
      m_draggingSpeedSlider = false;
    }
  } else if (event.type == sf::Event::MouseMoved) {
    // If we are dragging a slider, update it
    if (m_draggingSizeSlider || m_draggingSpeedSlider) {
      sf::Vector2f mousePos = window.mapPixelToCoords(
          sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
      updateSlider(mousePos);
    }
  }

  void UserInteractions::onLeftClick(const sf::Vector2f &mousePos,
                                     ParticleSystem &particleSystem) {
    // If we are in "AddParticles" mode and we have a valid right-click start:
    if (m_currentInteractionType == InteractionType::AddParticles &&
        m_hasRightClickStart) {
      // Speed vector is from right-click pos to left-click pos
      // if distance is longer, then the speed is higher
      sf::Vector2f speed = (mousePos - m_rightClickPosition) *
                           (mousePos - m_rightClickPosition) / 5;
      // to make non linear speed change, gives more control to the user

      // Build a vector of new Particles to add
      std::vector<Particle> newParticles;

      Particle p( // create a particle
          Vector2D(m_rightClickPosition.x, m_rightClickPosition.y), // position
          Vector2D(speed.x, speed.y),                               // velocity
          m_particleSize,                                           // radius
          1,    // type, for now only one type, TODO1: github issue  #3
          1.0f, // charge
          1.0f  // density
          ) newParticles.push_back(p);

      // Particle::Particle(Vector2D position, Vector2D velocity, float radius,
      // int type,
      //                float charge, float density)
      newParticles.push_back(p);

      // Bulk-add to the ParticleSystem
      particleSystem.addParticles(newParticles);
    }
  }
  void UserInteractions::onRightClick(const sf::Vector2f &mousePos) {
    m_hasRightClickStart = true;
    m_rightClickPosition = mousePos;
  }
  void UserInteractions::checkClicklocation(const sf::Vector2f &mousePos) {
    // check it is slider or button, and which one
    for (int i = 0; i < sliders.size(); i++) {
      sf::FloatRect field(sliders[i].slidebarX, sliders[i].slidebarY,
                          sliders[i].slidebarLength, sliders[i].slidebarWidth);
      if (addParticlesIconRect.contains(mousePos) &&
          i == 0) { // hard coded for now, only one slider and one button
        m_draggingSpeedSlider = true;
        updateSlider(mousePos);
      }
    }
    for (int i = 0; i < buttons.size(); i++) {
      sf::FloatRect field(buttons[i].start_point.x, buttons[i].start_point.y,
                          buttons[i].iconSizeX, buttons[i].iconSizeY);
      if (field.contains(
              mousePos &&
              i == 0)) { // hard coded for now, only one slider and one button
        buttons[i].pressed = !buttons[i].pressed;
        // Switch to AddParticles mode
        m_currentInteractionType = InteractionType::AddParticles;
        std::cout << "Switched to AddParticles mode\n";
      }
    }
    if (addParticlesIconRect.contains(mousePos)) {
      // Switch to AddParticles mode
      m_currentInteractionType = InteractionType::AddParticles;
      std::cout << "Switched to AddParticles mode\n";
    }
  }
