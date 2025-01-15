#include "global_var.hpp"
#include "Particle.hpp"
#include "Physics.hpp"
#include "Renderer.hpp"
#include "ParticleSystem.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void constant_flow(int flow_rate, ParticleSystem& particleSystem, int type) {
    static int counter = 0;
    if (counter % flow_rate == 0) {
        particleSystem.addParticle(Particle(Vector2D(100, 100), Vector2D(0, 0), 10, 1));
    }
    counter++;
}