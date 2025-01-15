#include "Particle.hpp"
Particle::Particle(Vector2D position, Vector2D velocity, float radius, int type,
                   float charge, float density)
    // TODO3: only denstiry, no mass for now, it is calcualted from density but
    // not the other way around
    : m_position(position), m_velocity(velocity), m_radius(radius),
      m_charge(charge), type(type), border()

{
  setDensity(density);
}

Vector2D Particle::getPosition() const { return m_position; }

Vector2D Particle::getVelocity() const { return m_velocity; }

float Particle::getRadius() const { return m_radius; }

float Particle::getCharge() const { return m_charge; }
float Particle::getMass() const { return mass; }
float Particle::getDensity() const { return density; }
int Particle::getType() const { return type; }
int Particle::getElasticity() const { return elasticity; }

void Particle::setPosition(const Vector2D &pos) { m_position = pos; }

void Particle::setVelocity(const Vector2D &vel) { m_velocity = vel; }

void Particle::setCharge(float c) { m_charge = c; }
void Particle::setDensity(float d) {
  density = d;
  mass = density * 4 / 3 * M_PI * m_radius * m_radius * m_radius;
}
void Particle::setMass(float m) {
  mass = m;
  density = mass / (4 / 3 * M_PI * m_radius * m_radius * m_radius);
}
void Particle::setType(int t) { type = t; }
void Particle::setElasticity(float e) { elasticity = e; }

void Particle::limit_coordinates(int fieldSizeX, int fieldSizeY,
                                 int fieldstartX, int fieldstartY) {
  if (m_position.x < fieldstartX) {
    m_position.x = fieldstartX;
  }
  if (m_position.x > fieldSizeX) {
    m_position.x = fieldSizeX;
  }
  if (m_position.y < fieldstartY) {
    m_position.y = fieldstartY;
  }
  if (m_position.y > fieldSizeY) {
    m_position.y = fieldSizeY;
  }
}
void Particle::update(float deltaTime) {
  // Simple Euler integration
  m_position.x += m_velocity.x * deltaTime;
  m_position.y += m_velocity.y * deltaTime;
}
