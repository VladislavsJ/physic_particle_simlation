// graphical_items.cpp
#include "graphical_items.hpp"
#include <SFML/Graphics.hpp>

// Slidebar constructor
Slidebar::Slidebar(float slidebarLength, float slidebarWidth, float slidebarX,
                   float slidebarY, float maxValue, float minValue,
                   sf::Color bodyColor, sf::Color pinColor)
    : slidebarX(slidebarX), slidebarY(slidebarY),
      slidebarLength(slidebarLength), slidebarWidth(slidebarWidth),
      maxValue(maxValue), minValue(minValue), currentValue(minValue),
      bodyColor(bodyColor), pinColor(pinColor) {}

void Slidebar::renderSlidebar(sf::RenderWindow &window) const {
  // Draw slidebar body
  sf::RectangleShape body(sf::Vector2f(slidebarLength, slidebarWidth));
  body.setPosition(slidebarX, slidebarY);
  body.setFillColor(bodyColor);
  window.draw(body);

  // Draw the pin
  float ratio = (currentValue - minValue) / (maxValue - minValue);
  float pinX = slidebarX + ratio * slidebarLength;

  // 1.2f is the scale for the circle(pin)
  const float pinScale = 1.2f;
  sf::CircleShape pin((slidebarWidth * 0.5f) * pinScale);
  pin.setPosition(pinX, slidebarY);
  pin.setFillColor(pinColor);
  window.draw(pin);
}

void Slidebar::updateSlider(sf::Vector2f mousePos) {
  // limit pin X position
  float pinX = std::clamp(mousePos.x, slidebarX, slidebarX + slidebarLength);

  // Update the currentValue based on pinX
  currentValue =
      minValue + (maxValue - minValue) * (pinX - slidebarX) / slidebarLength;
}

float Slidebar::getCurrentValue() const { return currentValue; }

bool Slidebar::PointOnTheSlider(sf::Vector2f mousePos) {
  // check if the mouse is on the slider
  return mousePos.x >= slidebarX && mousePos.x <= slidebarX + slidebarLength &&
         mousePos.y >= slidebarY && mousePos.y <= slidebarY + slidebarWidth;
}

switch_button::switch_button(float iconSizeX, float iconSizeY,
                             Vector2D start_point, sf::Color iconColor_ON,
                             sf::Color iconColor_OFF)
    : iconSizeX(iconSizeX), iconSizeY(iconSizeY), start_point(start_point),
      pressed(false), iconColor_ON(iconColor_ON), iconColor_OFF(iconColor_OFF) {
}

void switch_button::renderButton(sf::RenderWindow &window) const {
  sf::RectangleShape body(sf::Vector2f(iconSizeX, iconSizeY));
  body.setPosition(start_point.x, start_point.y);
  body.setFillColor(pressed ? iconColor_ON : iconColor_OFF);
  window.draw(body);
}

bool switch_button::PointOnTheSlider(sf::Vector2f mousePos) {
  // check if the mouse is on the slider
  return mousePos.x >= start_point.x &&
         mousePos.x <= start_point.x + iconSizeX &&
         mousePos.y >= start_point.y && mousePos.y <= start_point.y + iconSizeY;
}

void switch_button::updateButton(sf::Vector2f mousePos) {
  // Update the value of the button
  if (PointOnTheSlider(mousePos)) {
    pressed = !pressed;
  }
}