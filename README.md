# PhysicsEngine
Simple Physics Engine made following the book from Ian Milling "Game Physics Engine Design"

The project uses the demos created in the CD that comes with the book, to check if the calculations I made are correct, I simply
copied my files and replaced his, filling the gap with the code he made to make each demo work.

### Currently features implemented: 
- **Mathematics of Particle (Specifically the Vector class and operations to manipulate them)**
    - Vector Class
    - Operations to manipulate Vectors
- **Laws of Motions**
    - Particle Class
    - Introduction of First and Second law
    - Integrator function
- **Force Generators**
    - Added force Accumulator to Particle
    - Created Gravity Force Generator
- **Hook's Law**
    - Springlike Force Generators
    - Created a bunch of spring-like generators (Buoyancy, Stiff Spring, Anchored Spring, ...)
- **Hard constraint**
    - Particle contact and collisions (detection, change velocity after collision and handle interpenetration)
    - Particle Links class (Cables and Rods)

### To be implemented:
- **The Matemathics of Rotations (Chapter 9)**
- **Chapters after**
