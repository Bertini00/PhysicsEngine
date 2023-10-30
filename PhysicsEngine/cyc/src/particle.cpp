#include <include/particle.h>
#include <assert.h>
#include <float.h>

using namespace cyclone;

void Particle::setInverseMass(const real inverseMass) {
	Particle::inverseMass = inverseMass;
}

void Particle::setMass(const real mass) {
	assert(mass != 0);
	Particle::inverseMass = ((real)1.0)/mass;
}

real Particle::getInverseMass() const {
	return inverseMass;	
}

real Particle::getMass() const {
	if (inverseMass == 0)
	{
		return REAL_MAX;
	}
	else
	{
		return ((real)1.0) / inverseMass;
	}
}

void Particle::integrate(real duration) {
	assert(duration > 0.0);
	
	// Update linear position
	position.addScaledVector(velocity, duration);

	// Work out the acceleration from the force
	Vector3 resultingAcceleration = acceleration;
	resultingAcceleration.addScaledVector(forceAccum, inverseMass);

	// Update linear velocity
	velocity.addScaledVector(resultingAcceleration, duration);

	// Impose drag
	velocity *= real_pow(damping, duration);

	forceAccum.clear();

}

bool Particle::hasFiniteMass() const{
	return inverseMass >= 0.0f;
}

void Particle::setDamping(const real damping) {
	Particle::damping = damping;
}

real Particle::getDamping() const {
	return damping;
}

Vector3 Particle::getPosition() const {
	return position;
}

void Particle::setPosition(const Vector3& position) {
	Particle::position = position;
}

void Particle::setPosition(const real x, const real y, const real z) {
	Particle::position.x = x;
	Particle::position.y = y;
	Particle::position.z = z;
}

void Particle::getPosition(Vector3* position) const {
	*position = Particle::position;
}

void Particle::setVelocity(const Vector3& velocity) {
	Particle::velocity = velocity;
}

void Particle::setVelocity(const real x, const real y, const real z) {
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

Vector3 Particle::getVelocity() const {
	return velocity;
}

void Particle::getVelocity(Vector3* velocity) const {
	*velocity = Particle::velocity;
}

void Particle::setAcceleration(const Vector3& acceleration) {
	Particle::acceleration = acceleration;
}

void Particle::setAcceleration(const real x, const real y, const real z) {
	acceleration.x = x;
	acceleration.y = y;
	acceleration.z = z;
}

Vector3 Particle::getAcceleration() const {
	return acceleration;
}

void Particle::getAcceleration(Vector3 *acceleration) const {
	*acceleration = Particle::acceleration;
}

void Particle::clearAccumulator() {
	forceAccum.clear();
}

void Particle::addForce(const Vector3& force) {
	forceAccum += force;
}