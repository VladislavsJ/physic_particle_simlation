#include "user_interface.hpp"

void UserInterface::addSlider(const Slidebar &slidebar) {
  sliders.push_back(slidebar);
}
void UserInterface::addButton(const switch_button &button,
                              InteractionType type) {
  buttons.push_back(std::make_pair(button, type));
}
void UserInterface::clearAllButtonStates() {
  for (auto &button_pair : buttons) {
    button_pair.first.change_state(false);
  }
}
InteractionType
UserInterface::update_all_items(const sf::Vector2f &mouse_position) {
  for (auto &button_pair : buttons) {
    if (button_pair.first.PointOnTheButton(mouse_position)) {

      if (button_pair.first.pressed) { // if already pressed, clear all, NONE
        clearAllButtonStates();
        return InteractionType::None;
      } else {
        clearAllButtonStates();
        button_pair.first.updateButton(mouse_position);
        return button_pair.second;
      }
    }
  }
  for (Slidebar &slider : sliders) {
    if (slider.PointOnTheSlider(mouse_position)) {
      slider.updateSlider(mouse_position);
      return InteractionType::Slider;
    }
  }
  return InteractionType::None;
}

std::vector<Slidebar> UserInterface::getSliders() const { return sliders; }
std::vector<std::pair<switch_button, InteractionType>>
UserInterface::getButtons_interaction() const {
  return buttons;
}

InteractionType UserInterface::getCurrentInteractionType(
    const sf::Vector2f &mouse_position) const {
  if (mouse_position.x < gv.getFieldSizeX()) {
    return InteractionType::None;
  }
  for (auto &button_pair : buttons) {
    if (button_pair.first.PointOnTheButton(mouse_position)) {
      return button_pair.second;
    }
  }
  for (const Slidebar &slider : sliders) {
    if (slider.PointOnTheSlider(mouse_position)) {
      return InteractionType::Slider;
    }
  }
  return InteractionType::None;
}