#ifndef USER_INTERACTIONS_HPP
#define USER_INTERACTIONS_HPP

#include "ParticleSystem.hpp"
#include <SFML/Graphics.hpp>

// We can define different interactions (e.g. AddParticles, RemoveParticles,
// etc.)
enum class InteractionType { None, AddParticles };

class UserInteractions {
public:
  UserInteractions();

  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   ParticleSystem &particleSystem);

  InteractionType getCurrentInteractionType() const;

  // Sliders for size and speed:
  //  (You might store these in a global, or keep them here as part of the
  //  user’s state.)
  float getParticleSize() const;
  float getParticleSpeed() const;

private:
  // Internal helper to handle left/right clicks
  void onLeftClick(const sf::Vector2f &mousePos,
                   ParticleSystem &particleSystem);
  void onRightClick(const sf::Vector2f &mousePos);

  // If user clicked an icon in the 200px right panel
  void checkIconClick(const sf::Vector2f &mousePos);

  // If user clicked on slider in the 200px right panel
  void checkSliderClick(const sf::Vector2f &mousePos);
  void updateSlider(const sf::Vector2f &mousePos);

private:
  InteractionType m_currentInteractionType;

  bool m_hasRightClickStart;
  sf::Vector2f m_rightClickPosition;

  // For demonstration, store the slider positions and corresponding values
  float m_particleSize;  // e.g., 1..50
  float m_particleSpeed; // e.g., 0..500
  bool m_draggingSizeSlider;
  bool m_draggingSpeedSlider;
};

#endif // USER_INTERACTIONS_HPP
