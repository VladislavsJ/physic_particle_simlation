#include "Graphs_new.hpp"
#include "ParticleSystem.hpp"
#include "global_var.hpp"
#include "user_interactions.hpp"
#include <SFML/Graphics.hpp>

class Slidebar {
public:
  // Constructor
  Slidebar(float slidebarLength, float slidebarWidth, float slidebarX,
           float slidebarY, float maxValue, float minValue,
           sf::Color bodyColor = sf::Color(100, 100, 100),
           sf::Color pinColor = sf::Color(240, 80, 80));

  // Member function to get current value
  float getCurrentValue() const;
  void renderSlidebar(sf::RenderWindow &window);

private:
  float slidebarX; // Position of the slidebar
  float slidebarY;

  float slidebarLength;
  float slidebarWidth;

  float maxValue;
  float minValue;
  float currentValue;

  sf::Color bodyColor;
  sf::Color pinColor;
};

Slidebar::Slidebar(float slidebarLength, float slidebarWidth, float slidebarX,
                   float slidebarY, float maxValue, float minValue,
                   sf::Color bodyColor, sf::Color pinColor)
    : slidebarLength(slidebarLength), slidebarWidth(slidebarWidth),
      slidebarX(slidebarX), slidebarY(slidebarY), maxValue(maxValue),
      minValue(minValue),
      currentValue(minValue), // Default current value to minimum value
      bodyColor(bodyColor), pinColor(pinColor) {}

// Member function implementation
float Slidebar::getCurrentValue() const { return currentValue; }

class switch_button {
public:
  Button(float iconSizeX, float iconSizeY, Vector2D start_point,
         sf::Color iconColor_ON = (sf::Color::Green, sf:),
         sf::Color iconColor_OFF = sf::Color::Red);
  float iconSizeX;
  float iconSizeY;
  Vector2D start_point;
  bool pressed;
  sf::Color iconColor_ON;
  sf::Color iconColor_OFF;

} Button::Button(float iconSizeX, float iconSizeY, Vector2D start_point,
                 sf::Color iconColor_ON, sf::Color iconColor_OFF)
    : iconSizeX(iconSizeX), iconSizeY(iconSizeY), start_point(start_point),
      iconColor_ON(iconColor_ON), iconColor_OFF(iconColor_OFF) {
}