#include "Particle.hpp"
#include <SFML/Graphics.hpp>
Particle::Particle(Vector2D position, Vector2D velocity, float radius, int type,
                   float charge, float density, sf::Color color)
    : m_position(position), m_velocity(velocity), m_radius(radius),
      m_charge(charge), m_type(type), border() {
  setDensity(density), setColor(color);
} // TODO3: only denstiry, no mass for now, mass is calcualted from density but
  // not the other way around

// Getters
Vector2D Particle::getPosition() const { return m_position; }

Vector2D Particle::getVelocity() const { return m_velocity; }

float Particle::getRadius() const { return m_radius; }

float Particle::getCharge() const { return m_charge; }

float Particle::getMass() const { return m_mass; }

float Particle::getDensity() const { return m_density; }

int Particle::getType() const { return m_type; }

int Particle::getElasticity() const { return m_elasticity; }
sf::Color Particle::getColor() const { return m_color; }
// Setters
void Particle::setPosition(const Vector2D &position) { m_position = position; }

void Particle::setVelocity(const Vector2D &velocity) { m_velocity = velocity; }

void Particle::setCharge(float charge) { m_charge = charge; }

void Particle::setDensity(float density) {
  m_density = density;
  m_mass = (4.0f / 3.0f) * M_PI * m_radius * m_radius * m_radius * m_density;
}

void Particle::setMass(float mass) {
  m_mass = mass;
  m_density = mass / ((4.0f / 3.0f) * M_PI * m_radius * m_radius * m_radius);
}
void Particle::setColor(sf::Color color) { m_color = color; }

void Particle::setType(int type) { m_type = type; }

void Particle::setElasticity(float elasticity) { m_elasticity = elasticity; }

// Methods
void Particle::limitCoordinates(int fieldSizeX, int fieldSizeY, int fieldStartX,
                                int fieldStartY) {
  if (m_position.x < fieldStartX) {
    m_position.x = fieldStartX;
  } else if (m_position.x > fieldSizeX) {
    m_position.x = fieldSizeX;
  }

  if (m_position.y < fieldStartY) {
    m_position.y = fieldStartY;
  } else if (m_position.y > fieldSizeY) {
    m_position.y = fieldSizeY;
  }
}

void Particle::update(float deltaTime) {
  m_position.x += m_velocity.x * deltaTime;
  m_position.y += m_velocity.y * deltaTime;
}
sf::Color Particle::changeColor_Fspeed() const {
  // this function is mostly for debugging purposes, as it is not logical where
  // it is placed, but it is a good way to see  each particle speed.
  float speed =
      std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

  // colors
  sf::Color blue = sf::Color(0, 0, 255);     // Slowest
  sf::Color red = sf::Color(255, 0, 0);      // Fastest (in the range 0-1000)
  sf::Color yellow = sf::Color(255, 255, 0); // Speeds > 2000

  // Interpolate between colors
  if (speed <= 200) {
    float t = speed / 200.0f; // Normalize speed to [0, 1]
    return sf::Color(static_cast<sf::Uint8>(blue.r + t * (red.r - blue.r)),
                     static_cast<sf::Uint8>(blue.g + t * (red.g - blue.g)),
                     static_cast<sf::Uint8>(blue.b + t * (red.b - blue.b)));
  } else if (speed > 600) {
    return yellow; // Directly return yellow for high speeds, to find bugs
  } else {
    return sf::Color(sf::Color::Red);
  }
}