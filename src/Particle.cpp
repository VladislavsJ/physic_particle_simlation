#include "Particle.hpp"

Particle::Particle(Vector2D position, Vector2D velocity, float radius, float charge)
    : m_position(position),
      m_velocity(velocity),
      m_radius(radius),
      m_charge(charge)
{
}

Vector2D Particle::getPosition() const {
    return m_position;
}

Vector2D Particle::getVelocity() const {
    return m_velocity;
}

float Particle::getRadius() const {
    return m_radius;
}

float Particle::getCharge() const {
    return m_charge;
}

void Particle::setPosition(const Vector2D& pos) {
    m_position = pos;
}

void Particle::setVelocity(const Vector2D& vel) {
    m_velocity = vel;
}

void Particle::setCharge(float c) {
    m_charge = c;
}

void Particle::update(float deltaTime) {
    // Simple Euler integration
    m_position.x += m_velocity.x * deltaTime;
    m_position.y += m_velocity.y * deltaTime;
}
