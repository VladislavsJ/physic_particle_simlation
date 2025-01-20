#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include "global_var.hpp"
#include "graphical_items.hpp"
#include <forward_list>
extern GlobalVar &gv;
enum class InteractionType;
class UserInterface {
private:
  std::vector<std::pair<switch_button, InteractionType>> buttons;

  std::vector<Slidebar> sliders; // function to update the value,
                                 // for eample global.cpp gravity

  void clearAllButtonStates(); // as only one button can be active at a time
  // before activation, other should be deactivated
public:
  void addSlider(const Slidebar &slidebar);
  void addButton(const switch_button &button, InteractionType type);
  std::vector<Slidebar> getSliders() const;
  std::vector<std::pair<switch_button, InteractionType>>
  getButtons_interaction() const;
  InteractionType update_all_items(
      const sf::Vector2f &mouse_position); // if any button exists at mouse
                                           // position, return interaction type
  // if it is a slider, update it and return SlideBar interaciton
  //  if ubtton, all other button states should be cleared
  InteractionType
  getCurrentInteractionType(const sf::Vector2f &mouse_position) const;
};
#endif // USER_INTERFACE_HPP