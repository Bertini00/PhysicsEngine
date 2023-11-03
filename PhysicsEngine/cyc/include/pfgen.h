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

class ParticleSpring : public ParticleForceGenerator
{
public:
	/*
	* Creates a new spring with the given parameters
	*/
	ParticleSpring(Particle* other, real springConstant, real restLength);

	/*
	* Applies the spring force to the given particle
	*/
	virtual void updateForce(Particle* particle, real duration);

private:
	/*
	* The particle at the other end of the spring
	*/
	Particle* other;

	/*
	Holds the spring constant
	*/
	real springConstant;

	/*
	Holds the rest length of the spring
	*/
	real restLength;

};

class ParticleAnchoredSpring : public ParticleForceGenerator
{
public:
	/*
	* Create a particle anchored spring with the given values
	*/
	ParticleAnchoredSpring(Vector3* anchor, real springConstant, real restLength);

	/*
	* Applies the spring force to the given particle
	*/
	virtual void updateForce(Particle* particle, real duration);


private:
	/*
	* The location of the anchored end of the spring
	*/
	Vector3* anchor;

	/*
	* The spring constant
	*/
	real springConstant;

	/*
	The rest length of the spring
	*/
	real restLength;

};

class ParticleBungee : public ParticleForceGenerator
{
public:
	/*
	* Creates the particle bungee with the given parameters
	*/
	ParticleBungee(Particle* other, real springConstant, real restLength);

	/*
	* Applies the force to the given particle
	*/
	virtual void updateForce(Particle* particle, real duration);

private:

	/*
	* Location of the other particle
	*/
	Particle* other;

	/*
	* Value of the spring constant
	*/
	real springConstant;

	/*
	* Rest length of the spring
	*/
	real restLength;

};

class ParticleBuoyancy : public ParticleForceGenerator
{
public:
	/*
	* Creates the generator with the given parameters
	*/
	ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity = 1000.0f);

	/*
	* Applies the force to the particle
	*/
	virtual void updateForce(Particle* particle, real duration);

private:

	/*
	* The maximum submersion depth of the object before it generates the maximum buoyancy force
	*/
	real maxDepth;

	/*
	* The volume of the object
	*/
	real volume;

	/*
	* The height of the water plane above y=0. The plane will be parallel to the xz plane
	*/
	real waterHeight;

	/*
	* Density of the liquid the object is submerged in
	* Pure water has a density of 1000 kg per cubic meter
	*/
	real liquidDensity;

};

/*
* A force generator that fakes a stiff spring force, and where one end is attached to a fixed point in space
*/
class ParticleFakeSpring : public ParticleForceGenerator
{
public:
	
	/*
	* Creates a new spring with the given parameters
	*/
	ParticleFakeSpring(Vector3* anchor, real springContant, real damping);

	/*
	* Applies the spring force to the given particle
	*/
	virtual void updateForce(Particle* particle, real duration);

private:
	/*
	* The location of the anchored end of the spring
	*/
	Vector3* anchor;

	/*
	* The spring constant
	*/
	real springConstant;

	/*
	* The damping of the oscillation of the spring
	*/
	real damping;


};

}