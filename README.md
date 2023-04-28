# Particle-System
Particle system that shoots out sprites from a source with adjustable variables

Variables can be adjusted using a GUI that uses wxWidgets, so you need to have wxWidgets installed.
There is also a ground that the particles can collide with and experience friction on.

Variables that can be adjusted include:

- Particle creation rate (particles per second)
- Initial position & variance (X, Y, Z)
- Initial velocity & variance (X, Y, Z)
- Initial life span & variance
- Gravity
- Air density
- Drag coefficient
- Particle radius (for both rendering & aerodynamic drag)
- Collision elasticity
- Collision friction
