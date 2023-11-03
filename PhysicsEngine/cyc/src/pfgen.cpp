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

ParticleSpring::ParticleSpring(Particle* other, real springConstant, real restLength) {
	ParticleSpring::other = other;
	ParticleSpring::springConstant = springConstant;
	ParticleSpring::restLength = restLength;
}

void ParticleSpring::updateForce(Particle* particle, real duration) {
	// Calculate the vector of the spring
	Vector3 force;

	particle->getPosition(&force);
	force -= other->getPosition();

	// Calculate the magnitude of the force
	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate the final force
	force.normalize();
	force *= -magnitude;
	particle->addForce(force);
}

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3* anchor, real springConstant, real restLength) {
	ParticleAnchoredSpring::anchor = anchor;
	ParticleAnchoredSpring::springConstant = springConstant;
	ParticleAnchoredSpring::restLength = restLength;
}

void ParticleAnchoredSpring::updateForce(Particle* particle, real duration) {
	// Calculate the force
	Vector3 force;
	
	particle->getPosition(&force);
	force -= *anchor;

	// Calculate the magnitude of the force
	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate the final force
	force.normalize();
	force *= -magnitude;
	particle->addForce(force);
}


ParticleBungee::ParticleBungee(Particle* other, real springConstant, real restLength) {
	ParticleBungee::other = other;
	ParticleBungee::springConstant = springConstant;
	ParticleBungee::restLength = restLength;
}

void ParticleBungee::updateForce(Particle* particle, real duration) {
	// Calculate the vector of the spring
	Vector3 force;
	particle->getPosition(&force);
	force -= other->getPosition();

	// Calculate the magnitude of the spring
	real magnitude = force.magnitude();
	if (magnitude <= restLength) return;
	magnitude = springConstant * real_abs(magnitude - restLength);

	// Calculate the final force
	force.normalize();
	force *= -magnitude;
	particle->addForce(force);

}

ParticleBuoyancy::ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity) {
	ParticleBuoyancy::maxDepth = maxDepth;
	ParticleBuoyancy::volume = volume;
	ParticleBuoyancy::waterHeight = waterHeight;
	ParticleBuoyancy::liquidDensity = liquidDensity;
}

void ParticleBuoyancy::updateForce(Particle* particle, real duration) {
	
	// Calculate the depth of the particle
	real depth = particle->getPosition().y;

	// Completely out of the water
	if (depth >= waterHeight + maxDepth) return;
	Vector3 force(0, 0, 0);

	if (depth <= waterHeight - maxDepth) 
	{
		// Fully submerged
		force.y = liquidDensity * volume;
		particle->addForce(force);
		return;
	}

	// The block is partially submerged
	real d = (depth - waterHeight - maxDepth) / 2 * maxDepth;
	force.y = liquidDensity * volume * d;
	particle->addForce(force);


}

ParticleFakeSpring::ParticleFakeSpring(Vector3* anchor, real springConstant, real damping) {
	ParticleFakeSpring::anchor = anchor;
	ParticleFakeSpring::springConstant = springConstant;
	ParticleFakeSpring::damping = damping;
}

void ParticleFakeSpring::updateForce(Particle* particle, real duration) {
	if (!particle->hasFiniteMass()) return;

	// Calculate the relative position of the particle to the anchor
	Vector3 position;
	position = particle->getPosition() - *anchor;

	// Calculate the constant and check whether they are in bounds
	real gamma = 0.5f * real_sqrt(4 * springConstant - damping * damping);
	if (gamma == 0.0f) return;
	Vector3 c = position * (damping / 2.0f * gamma) + particle->getVelocity() * (1.0f / gamma);

	// Calculate the target position

	Vector3 finalPosition = (position * real_cos(gamma * duration) + c * real_sin(gamma * duration)) * real_exp(-0.5f * damping * duration);

	// Calculate the resulting acceleration and the force
	Vector3 finalAcceleration = (finalPosition - position) * (1.0f / duration * duration) - particle->getVelocity() * duration;

	particle->addForce(finalAcceleration * particle->getMass());
	
}