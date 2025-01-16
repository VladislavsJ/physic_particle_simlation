#include "user_interactions.hpp"
#include "Particle.hpp"   // For creating new Particles
#include "global_var.hpp" // Assuming you need gv.getFieldSizeX(), etc.
#include <iostream>

extern GlobalVar &gv;

UserInteractions::UserInteractions()
    : m_currentInteractionType(InteractionType::None),
      m_hasRightClickStart(false), m_particleSize(20.0f) // Default slider value
      ,
      m_particleSpeed(100.0f) // Default slider value
      ,
      m_draggingSizeSlider(false), m_draggingSpeedSlider(false) {}

void UserInteractions::handleEvent(const sf::Event &event,
                                   sf::RenderWindow &window,
                                   ParticleSystem &particleSystem) {
  // We only do more specific checking if it's a mouse event
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePos = window.mapPixelToCoords(
          sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

      // Check if the click is within the right panel or in the main field
      if (mousePos.x >= gv.getFieldSizeX()) {
        // The click is in the 200px right panel
        checkIconClick(mousePos);
        checkSliderClick(mousePos);
      } else {
        // The click is in the main field
        onLeftClick(mousePos, particleSystem);
      }
    } else if (event.mouseButton.button == sf::Mouse::Right) {
      sf::Vector2f mousePos = window.mapPixelToCoords(
          sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

      // Only if in the main field area
      if (mousePos.x < gv.getFieldSizeX()) {
        onRightClick(mousePos);
      }
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
}

void UserInteractions::onLeftClick(const sf::Vector2f &mousePos,
                                   ParticleSystem &particleSystem) {
  // If we are in "AddParticles" mode and we have a valid right-click start:
  if (m_currentInteractionType == InteractionType::AddParticles &&
      m_hasRightClickStart) {
    // Speed vector is from right-click pos to left-click pos
    sf::Vector2f speed = mousePos - m_rightClickPosition;

    // Build a vector of new Particles to add
    std::vector<Particle> newParticles;

    // For this example, we only add one particle.
    // You can push_back multiple if you want more.
    Particle p(
        Vector2D(m_rightClickPosition.x, m_rightClickPosition.y), // position
        Vector2D(speed.x, speed.y),                               // velocity
        m_particleSize,                                           // radius
        1.0f // mass, or use your logic
    );
    newParticles.push_back(p);

    // Bulk-add to the ParticleSystem
    particleSystem.addParticles(newParticles);

    // We can reset the right-click so we only do one add each time
    m_hasRightClickStart = false;
  }
}

void UserInteractions::onRightClick(const sf::Vector2f &mousePos) {
  m_hasRightClickStart = true;
  m_rightClickPosition = mousePos;
}

void UserInteractions::checkIconClick(const sf::Vector2f &mousePos) {
  // Example: Suppose we have a small square “AddParticles icon”
  // at (gv.getFieldSizeX() + 20, 20) with size 32x32
  sf::FloatRect addParticlesIconRect(gv.getFieldSizeX() + 20, 20, 32, 32);

  if (addParticlesIconRect.contains(mousePos)) {
    // Switch to AddParticles mode
    m_currentInteractionType = InteractionType::AddParticles;
    std::cout << "Switched to AddParticles mode\n";
  }
}

void UserInteractions::checkSliderClick(const sf::Vector2f &mousePos) {
  // Suppose we have two sliders:
  // 1) Size slider from (gv.getFieldSizeX()+10, 100) to
  // (gv.getFieldSizeX()+190, 120) 2) Speed slider from (gv.getFieldSizeX()+10,
  // 150) to (gv.getFieldSizeX()+190, 170) We store the “knob” positions in
  // m_particleSize, m_particleSpeed, but we must detect if the user is clicking
  // on the slider zone.

  // Size slider area
  sf::FloatRect sizeSliderRect(gv.getFieldSizeX() + 10, 100,
                               180, // width
                               20   // height
  );
  if (sizeSliderRect.contains(mousePos)) {
    m_draggingSizeSlider = true;
    updateSlider(mousePos);
  }

  // Speed slider area
  sf::FloatRect speedSliderRect(gv.getFieldSizeX() + 10, 150,
                                180, // width
                                20   // height
  );
  if (speedSliderRect.contains(mousePos)) {
    m_draggingSpeedSlider = true;
    updateSlider(mousePos);
  }
}

void UserInteractions::updateSlider(const sf::Vector2f &mousePos) {
  // For a simple linear slider from xStart..xEnd, map to [minValue..maxValue]
  float xStart = gv.getFieldSizeX() + 10;
  float xEnd = gv.getFieldSizeX() + 190;
  float width = xEnd - xStart;             // 180
  float t = (mousePos.x - xStart) / width; // range [0..1]

  // clamp t
  if (t < 0.f)
    t = 0.f;
  if (t > 1.f)
    t = 1.f;

  // For this example, let’s define:
  // m_particleSize: range 1..50
  // m_particleSpeed: range 0..500

  if (m_draggingSizeSlider) {
    float minSize = 1.f;
    float maxSize = 50.f;
    m_particleSize = minSize + t * (maxSize - minSize);
  }
  if (m_draggingSpeedSlider) {
    float minSpeed = 0.f;
    float maxSpeed = 500.f;
    m_particleSpeed = minSpeed + t * (maxSpeed - minSpeed);
  }
}

// Getters:
InteractionType UserInteractions::getCurrentInteractionType() const {
  return m_currentInteractionType;
}

float UserInteractions::getParticleSize() const { return m_particleSize; }

float UserInteractions::getParticleSpeed() const { return m_particleSpeed; }
