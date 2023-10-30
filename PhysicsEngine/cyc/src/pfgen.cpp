#include <include/pfgen.h>

using namespace cyclone;

void ParticleForceRegistry::updateForces(real duration) {
	Registry::iterator i = registrations.begin();
	for (; i != registrations.end(); i++)
	{
		i->fg->updateForce(i->particle, duration);
	}
}

ParticleGravity::ParticleGravity(Vector3& gravity) {

	ParticleGravity::gravity = gravity;
}

void ParticleGravity::updateForce(Particle* particle, real duration) {

	// Is immovable
	if (!particle->hasFiniteMass()) return;

	// Applies the mass scaled force to the particle
	particle->addForce(gravity * particle->getMass());
}

ParticleDrag::ParticleDrag(real k1, real k2)
{
	ParticleDrag::k1 = k1;
	ParticleDrag::k2 = k2;
}

void ParticleDrag::updateForce(Particle* particle, real duration) {

	Vector3 force;
	particle->getVelocity(&force);

	// Calculate the total drag force
	real dragCoeff = force.magnitude();
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

	// Calculate the final force and apply it	
	force.normalize();
	force *= -dragCoeff;
	particle->addForce(force);
}