#pragma once
#include "core.h"
using namespace cyclone;

namespace cyclone {


/*
* A particle is the simplest object that can be simulated in the physics system
*/
class Particle
{
public:

	/*
	* Holds the linear position of the particle in the world space
	*/
	Vector3 position;

	/*
	* Holds the linear velocity of the particle in the world space
	*/
	Vector3 velocity;

	/*
	* Holds the linear acceleration of the particle. This value can be used
	* to set acceleration due to gravity or any other constant acceleration
	*/
	Vector3 acceleration;

	/*
	* Holds the amount of damping applied to linear motion. 
	* Damping is required to remove energy added through numerical instability in the integrator
	*/
	real damping;



	
protected:
	/*
	* Holds the inverse of the mass of the particle. It is more useful because integration is simplier
	* and because it is easier to represent infinite (immovable object) mass than zero mass
	*/
	real inverseMass;


	/*
	* Holds the accumulated force to be applied to the next integration step only.
	* Get reset to zero after each integration step
	*/
	Vector3 forceAccum;


public:
	/*
	* Set the value of inverse mass to the mass passed
	* 
	* @param mass The new mass of the particle
	*/
	void setMass(const real mass);

	/*
	* Get the mass of the particle
	* 
	* @return The current mass of the particle
	*/
	real getMass() const;

	/*
	* Set the value of inverse mass to the inverse mass passed
	* 
	* @param inverseMass The new inverse mass of the particle
	*/
	void setInverseMass(const real inverseMass);

	/*
	* Gets the inverse mass of the particle
	* 
	* @return The current inverse mass of the particle
	*/
	real getInverseMass() const;

	/*
	* Returns true if the particle has non-infinite mass
	*/
	bool hasFiniteMass() const;

	/*
	* Set the value of the damping of the particle
	*/
	void setDamping(const real damping);

	/*
	* Gets the current damping of the particle
	* 
	* @return The current damping of the particle
	*/
	real getDamping() const;


	/*
	* Integrates the particle forward in time by the given amount
	* This function uses a Newton-Euler integration method, which is a linear
	* aproximation and may be inaccurate in some cases
	*/
	void integrate(real duration);

	/*
	* Get the position of the particle
	* 
	* @return The current position of the particle
	*/
	Vector3 getPosition() const;

	/*
	* Set the position of the particle
	* 
	* @param position The new position of the particle
	*/
	void setPosition(const Vector3& position);

	/*
	* Set the position of the particle
	* 
	* @param x The x coordinate of the position
	* @param y The y coordinate of the position
	* @param z The z coordinate of the position
	*/
	void setPosition(const real x, const real y, const real z);

	/**
	* Fill the given vector with the position of the particle
	* 
	* @param position A pointer to a vector into which to write the position of the particle
	*/
	void getPosition(Vector3* position) const;

	/*
	* Set the velocity of the particle
	* 
	* @param velocity The new velocity of the particle
	*/
	void setVelocity(const Vector3& velocity);

	/*
	* Set the velocity of the particle
	* 
	* @param x The x value of the new velocity of the particle
	* @param y The y value of the new velocity of the particle
	* @param z The z value of the new velocity of the particle
	*/
	void setVelocity(const real x, const real y, const real z);

	/*
	* Get the velocity of the particle
	* 
	* @return The velocity of the particle
	*/
	Vector3 getVelocity() const;

	/*
	* Fills the given vector with the current velocity of the particle
	*
	* @param velocity The vector in which to put the velocity of the particle
	*/
	void getVelocity(Vector3 *velocity) const;

	/*
	* Sets the constant acceleration of the particle
	* 
	* @param acceleration The new acceleration of the particle
	*/
	void setAcceleration(const Vector3& acceleration);

	/*
	* Sets the constant acceleration of the particle
	* 
	* @param x the x value of the new acceleration of the particle
	* @param y the y value of the new acceleration of the particle
	* @param z the z value of the new acceleration of the particle
	*/
	void setAcceleration(const real x, const real y, const real z);

	/*
	* Get the acceleration of the particle
	* 
	* @return The acceleration of the particle
	*/
	Vector3 getAcceleration() const;

	/*
	* Fills the given vector with the current acceleration of the particle
	* 
	* @param acceleration The vector in which to put the acceleration
	*/
	void getAcceleration(Vector3* acceleration) const;

	/*
	* Clears the forces applied to the particle. This will be called automatically after each integration step
	*/
	void clearAccumulator();

	/*
	* Adds the given force to the particle, to be applied only the next integration step
	*/
	void addForce(const Vector3 &force);


private:

};

}