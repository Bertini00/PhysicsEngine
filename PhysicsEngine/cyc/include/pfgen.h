#pragma once
#include <include/particle.h>
#include <vector>

namespace cyclone {


class ParticleForceGenerator
{
public:
	/*
	* Overload this in implementations of the interface to calculate and update the force applied to a particle
	*/
	virtual void updateForce(Particle* particle, real duration) = 0;

private:

};

/*
* Holds all the force generators and all the particle they apply to
*/
class ParticleForceRegistry
{
protected:
	/*
	* Keeps track of one force generator and the particle it applies to
	*/
	struct ParticleForceRegistration {
		Particle* particle;
		ParticleForceGenerator* fg;
	};

	/*
	* Holds the list of registration
	*/
	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;

public:
	/*
	* Register the given force generator to apply to the given particle
	*/
	void add(Particle* particle, ParticleForceGenerator* fg);

	/*
	* Removes the given registered pairs from the registry.
	* If the pair is not registered this method has no effect
	*/
	void remove(Particle* particle, ParticleForceGenerator* fg);

	/*
	* Clears all registrations from the registry. This will not delete the particle or the force
	* generators, this will only delete the connections between them.
	*/
	void clear();

	/*
	* Calls all the force generators to update the forces of their 
	* corresponding particle
	*/
	void updateForces(real duration);

};

class ParticleGravity : public ParticleForceGenerator
{
public:
	/*
	* Creates the generator with the given vector
	*/
	ParticleGravity(Vector3& gravity);

	/*
	* Applies the gravity to the particle it is assigned to
	*/
	virtual void updateForce(Particle* particle, real duration);

	
private:

	/* Holds the acceleration of the gravity*/
	Vector3 gravity;

};

class ParticleDrag : public ParticleForceGenerator
{
public:
	/* Creates the generator with the given velocity coefficient */
	ParticleDrag(real k1, real k2);

	/* Applies the drag force to the given particle*/
	virtual void updateForce(Particle* particle, real duration);
private:

	/* Hold the velocity drag coefficient */
	real k1;

	/* Hold the velocity squared drag coefficient */
	real k2;

};

}