#ifndef PARTICLE_H
#define PARTICLE_H

#include "BorderInfo.hpp"
#include "Vector2D.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
// TODO LIST
// TODO0: High risk, must be fixed and thoroughly checked before use.
// TODO1: Important functionality, but the system may operate without it.
// TODO2: Ideas for optimization and enhancements; important but not critical.
// TODO3: Future considerations and potential improvements.

// Each particle represents a physical entity with specific attributes.
// Currently includes:
// - Two vectors: Position and Velocity
// - Radius, Charge, Mass, and Density
// TODO3: Implement functionality for particles to exert forces on each other
//(e.g., electrostatic). "MORE FORMULAS!!"

class Particle {
public:
  Particle(Vector2D position, Vector2D velocity, float radius = 25.0f,
           int type = 0, float charge = 0, float density = 1.0f,
           sf::Color color = sf::Color::White);

  // Getters
  Vector2D getPosition() const;
  Vector2D getVelocity() const;
  float getRadius() const;
  float getCharge() const;
  float getMass() const;
  float getDensity() const;
  int getType() const;
  int getElasticity() const;
  sf::Color getColor() const;
  // Setters
  void setPosition(const Vector2D &pos);
  void setVelocity(const Vector2D &vel);
  void setCharge(float c);
  void setDensity(float d);
  void setType(int t);
  void setMass(float m);
  void limitCoordinates(int fieldSizeX, int fieldSizeY, int fieldStartX = 0,
                        int fieldStartY = 0);
  void setElasticity(float e);
  sf::Color changeColor_Fspeed() const;
  void setColor(sf::Color color);
  // More like a bug hider: if a particle is out of the field, it will be set to
  // the border
  // TODO3: limitCoordinates should not be needed at all

  // Update method
  void update(float deltaTime);

public:
  BorderInfo border;

private:
  Vector2D m_position;
  Vector2D m_velocity;
  float m_radius;
  float m_charge;
  float m_mass;
  float m_density;
  float m_elasticity; // How much energy is lost in the collision
  int m_type;         // TODO3: For different particle types
  sf::Color m_color;  // TODO3:
};

#endif // PARTICLE_H
