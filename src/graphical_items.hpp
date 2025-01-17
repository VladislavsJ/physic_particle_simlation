#ifndef GRAPHICAL_ITEMS_HPP
#define GRAPHICAL_ITEMS_HPP

#include "Vector2D.hpp"
#include <SFML/Graphics.hpp>

class Slidebar {
public:
  // Constructor
  Slidebar(float slidebarLength, float slidebarWidth, float slidebarX,
           float slidebarY, float maxValue, float minValue,
           sf::Color bodyColor = sf::Color(100, 100, 100),
           sf::Color pinColor = sf::Color(240, 80, 80));

  void updateSlider(sf::Vector2f mousePos);
  bool PointOnTheSlider(sf::Vector2f mousePos);
  void renderSlidebar(sf::RenderWindow &window) const;

  float getCurrentValue() const;

  // Getters
  float getSlidebarLength() const { return slidebarLength; }
  float getSlidebarWidth() const { return slidebarWidth; }
  float getSlidebarX() const { return slidebarX; }
  float getSlidebarY() const { return slidebarY; }
  float getmaxValue() const { return maxValue; }
  float getminValue() const { return minValue; }
  float getcurrentValue() const { return currentValue; }

private:
  float slidebarX;
  float slidebarY;
  float slidebarLength;
  float slidebarWidth;
  float maxValue;
  float minValue;
  float currentValue;
  sf::Color bodyColor;
  sf::Color pinColor;
};

class switch_button {
public:
  // Constructor
  switch_button(float iconSizeX, float iconSizeY, Vector2D start_point,
                sf::Color iconColor_ON = sf::Color::Green,
                sf::Color iconColor_OFF = sf::Color::Red);

  void renderButton(sf::RenderWindow &window) const;
  bool PointOnTheSlider(sf::Vector2f mousePos);
  void updateButton(sf::Vector2f mousePos);

  float iconSizeX;
  float iconSizeY;
  Vector2D start_point;
  bool pressed;
  sf::Color iconColor_ON;
  sf::Color iconColor_OFF;
};

#endif // GRAPHICAL_ITEMS_HPP
