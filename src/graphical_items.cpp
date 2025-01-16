#include "graphical_items.hpp"

void Slidebar::renderSlidebar(sf::RenderWindow &window) {
  // Draw the body of the slidebar
  sf::RectangleShape body(sf::Vector2f(slidebarLength, slidebarWidth));
  body.setPosition(slidebarX, slidebarY);
  body.setFillColor(bodyColor);
  window.draw(body);

  // Draw the pin
  float pinX = slidebarX + (currentValue - minValue) / (maxValue - minValue) *
                               slidebarLength;
  // pin has variables coordinate, depending on the currentValue
  sf::CircleShape pin(
      (sliderWidth / 2 * 1.2)); // ball is 1.2 is the size of the pin
  pin.setPosition(pinX, slidebarY);
  pin.setFillColor(pinColor);
  window.draw(pin);
}
void switch_button::renderButton(sf::RenderWindow &window) {
  // Draw the body of the button
  sf::RectangleShape body(sf::Vector2f(iconSizeX, iconSizeY));
  body.setPosition(start_point.x, start_point.y);
  if (pressed)
    body.setFillColor(iconColor_ON);
  else
    body.setFillColor(iconColor_OFF);
  window.draw(body);
}