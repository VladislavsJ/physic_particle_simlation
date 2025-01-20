#ifndef USER_INTERACTIONS_new_HPP
#define USER_INTERACTIONS_new_HPP

#include "ParticleSystem.hpp"
#include "graphical_items.hpp"
#include "user_interface.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
enum class InteractionType;
class UserInteractions {
public:
  UserInteractions();

  // Called once at startup to create the sliders, buttons, etc.
  void initUI();

  // Called every time an event occurs
  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   ParticleSystem &particleSystem);

  InteractionType getCurrentInteractionType() const;
  std::vector<Slidebar> getSliders() const;
  std::vector<std::pair<switch_button, InteractionType>>
  getButtons_Interact() const;

private:
  // Helpers
  void onLeftClick(const sf::Vector2f &mousePos,
                   ParticleSystem &particleSystem);
  void onRightClick(const sf::Vector2f &mousePos);
  void MouseMoved(const sf::Vector2f &mousePos);

private:
  // Keep track of user’s chosen action
  InteractionType m_currentInteractionType;
  UserInterface m_userInterface = UserInterface();
  // Sliders & Buttons

  bool m_rightClickStart;
  sf::Vector2f m_rightClickPosition;
};

#endif // USER_INTERACTIONS_NEW_HPP
