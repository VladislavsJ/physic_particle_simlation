#ifndef USER_INTERACTIONS_new_HPP
#define USER_INTERACTIONS_new_HPP

#include "ParticleSystem.hpp"
#include "graphical_items.hpp"
#include <SFML/Graphics.hpp>

// We can define different interactions (e.g. AddParticles, RemoveParticles,
// etc.)
enum class InteractionType { None, AddParticles };

class UserInteractions {
public:
  UserInteractions();
  create_sliders_buttons(); // create all the sliders and buttons, for now all
                            // things are hard coded
  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   ParticleSystem &particleSystem);
  InteractionType getCurrentInteractionType() const;

private:
  // Internal helper to handle left/right clicks
  void onLeftClick(
      const sf::Vector2f &mousePos,
      ParticleSystem &particleSystem); // click was on the main field(simulator)
  void onRightClick(
      const sf::Vector2f &mousePos); // click was on the right panel(data)

  // If user clicked an icon in the 200px right panel
  void checkIconClick(const sf::Vector2f &mousePos);

  // If user clicked on slider,
  void checkSliderClick(const sf::Vector2f &mousePos);
  void updateSlider(const sf::Vector2f &mousePos);

private:
  InteractionType m_currentInteractionType;

  bool m_hasRightClickStart;
  sf::Vector2f
      m_rightClickPosition; // it is the spot from which balls will be created.
  std::vector<Slidebar> sliders;      // all sliders
  std::vector<switch_button> buttons; // all buttons
};

#endif // USER_INTERACTIONS_HPP
