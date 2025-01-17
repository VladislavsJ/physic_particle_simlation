![Screencast from 2025-01-17 17-47-33 (1)](https://github.com/user-attachments/assets/deaedaec-b53d-48e8-94af-223425de4f78)


Particle Simulator
A prototype particle simulation system inspired by Sandbox games, designed to test multi-core/CUDA performance on real-world tasks (coming soon).
Features

Interactive particle generation system
Adjustable particle properties (speed and size/mass)
Real-time performance monitoring
Particle count tracking
SFML-based display system
Modular design for easy component addition/deletion

How to Use

Click the red button to enable white ball generation
Use the slider bars to adjust:

Ball speed
Ball size (affects mass)


To create a new ball:

Enable white ball generation
Right-click to set ball spawn coordinates
Left-click to set direction vector
Ball speed is determined by the slider value and the distance between right and left clicks



Performance Monitoring
The simulation includes two real-time graphs:

Frame processing time
Total particle count

Project Structure
BorderInfo

BorderInfo.cpp: Contains the implementation of logic to save and check if particle have touched borders
BorderInfo.hpp

Globals

global_var.hpp: Defines global variables used across the simulation

Graphical Items

graphical_items.cpp: Implements visual elements displayed in the simulation (buttons, slide-bars)
graphical_items.hpp

Graphs

Graphs_new.cpp: Implements graph creation for FPS and particle count displaying

Note: Currently highly coupled with Renderer class - will be refactored in future


Graphs_new.hpp

Main

main.cpp: The entry point of the program. Sets up and runs the simulation

Particle

Particle.cpp: Implements the properties of individual particles
Particle.hpp

Particle System

ParticleSystem.cpp: Manages a collection of particles and their interactions
ParticleSystem.hpp

Physics

Physics.cpp: Handles the physics calculations for particle movements and border interactions
Physics.hpp

Renderer

Renderer.cpp: Implements rendering logic for displaying the simulation
Renderer.hpp

User Interactions

user_interactions_new.cpp: Handles user input and interaction with the simulation (left/right click)
user_interactions_new.hpp

Vector2D

Vector2D.hpp: Provides 2D vector class

Note: Planned for deprecation in favor of sf::Vector2f



Current Status
This project is in pre-pre-alpha stage. Known bugs exist but the developer will fix them right after coffee break
Dependencies

SFML library for display

Future Plans

Implementation of multi-core processing
CUDA performance chec/optimization
Bug fixes and stability improvements
Refactoring of coupled components
