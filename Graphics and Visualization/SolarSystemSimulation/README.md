# Solar System Simulation
The purpose of this assignment is to create the Solar system based on a Perspective Projection, using OpenGL, C++ and Shaders

### Features
* Imported models of all the planets in the Solar System
* Created the Sun at the center of the Solar System and applied illumination properties.
* Created 5 individual planets with the following features: 
  - Simuluating original size, movement, trace and luminosity
  - Each planet rotates around the Sun
  - Each planet rotates around its axis
* Implemented the Moon and simulated its rotation around the Earth
* Applied proper textures for each planet and a light map
* Camera POV to move across the scene using the mouse and keyboard keys (A,W,S,D)
* Asteroid features:
   - Is generated and launched from random locations of outer space when 'P' Button is pressed on keyboard
  - Asteroid is created via tracing
  - When the asteroid passes a close planet it'll change its trace based on the size of the planet only
  - When asteroid collides with the planet, asteroid will be destroyed
