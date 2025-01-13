#ifndef PARTICLE_H
#define PARTICLE_H
#include "BorderInfo.hpp"
 #include "Vector2D.hpp"
//TODO LIST
//TODO0: high risk, should be fixed, checked before use
// TODO1: Important functionality, but may work without it
// TODO2, Ideas for optimization, and important stuff, but not necessary
// TOOD3, just ideas for the future

//Each particle has its values,
//now it is 
//2 vectors, Velocity, Position 
// radius and charge
//TODO3 (particles can accelerate to each other, "MORE FORMULAS!!"
class Particle {
public:
    Particle(Vector2D position, Vector2D velocity, float radius, float charge);

    // Getters
    Vector2D getPosition() const;
    Vector2D getVelocity() const;
    float    getRadius()   const;
    float    getCharge()   const;
    
    // Setters
    void setPosition(const Vector2D& pos);
    void setVelocity(const Vector2D& vel);
    void setCharge(float c);

    // Update method
    void update(float deltaTime);

private:
    Vector2D m_position;
    Vector2D m_velocity;
    float    m_radius;
    float    m_charge;
    int type;//TODO3: for different particles types
    BorderInfo border;
};

#endif // PARTICLE_H
