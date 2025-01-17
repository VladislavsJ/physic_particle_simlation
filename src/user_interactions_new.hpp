#ifndef USER_INTERACTIONS_new_HPP
#define USER_INTERACTIONS_new_HPP

#include "ParticleSystem.hpp"
#include "graphical_items.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

enum class InteractionType { // interaction types, for each button
  None,
  AddParticles,
  White_Ball,
  Red_Ball
};

class UserInteractions {
public:
  UserInteractions();

  // Called once at startup to create the sliders, buttons, etc.
  void initUI();

  // Called every time an event occurs
  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   ParticleSystem &particleSystem);

  // Example getter
  InteractionType getCurrentInteractionType() const;

  // Provide access if you want your Renderer to draw them
  const std::vector<Slidebar> &getSliders() const { return m_sliders; }
  const std::vector<std::pair<switch_button, InteractionType>> &
  getButtons() const {
    return m_buttons;
  }

private:
  // Helpers
  void onLeftClick(const sf::Vector2f &mousePos,
                   ParticleSystem &particleSystem);
  void onRightClick(const sf::Vector2f &mousePos);
  void MouseMoved(const sf::Vector2f &mousePos);

  // For building up the UI
  void create_new_Slider(const Slidebar &slidebar);
  void create_new_Button(const switch_button &button, InteractionType type);

private:
  // Keep track of user’s chosen action
  InteractionType m_currentInteractionType;

  // Sliders & Buttons
  std::vector<Slidebar> m_sliders;
  std::vector<std::pair<switch_button, InteractionType>> m_buttons;

  bool m_rightClickStart;
  sf::Vector2f m_rightClickPosition;
};

#endif // USER_INTERACTIONS_NEW_HPP
