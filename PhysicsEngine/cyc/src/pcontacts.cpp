#include <include/pcontacts.h>

void ParticleContact::resolve(real duration) {
	resolveVelocity(duration);
	resolveInterpenetration(duration);
}

real ParticleContact::calculateSeparatingVelocity() const {
	Vector3 relativeVelocity = particle[0]->getVelocity();
	if (particle[1]) relativeVelocity -= particle[1]->getVelocity();
	return relativeVelocity * contactNormal;
}

void ParticleContact::resolveVelocity(real duration) {
	// Find the velocity in the direction of the contact
	real separatingVelocity = calculateSeparatingVelocity();
	if (separatingVelocity > 0)
	{
		// The contact is either stationary or is separatingd
		// No impulse required
		return;
	}
	// Calculate the new separating velocity
	real newSeparatingVelocity = -separatingVelocity * restitution;

	// Check the velocity build up due to acceleration only
	Vector3 accCausedVelocity = particle[0]->getAcceleration();
	if (particle[1]) accCausedVelocity -= particle[1]->getAcceleration();

	real accCausedSeparatingVelocity = accCausedVelocity * contactNormal * duration;

	// If we have a closing velocity due to acceleration buildup, remove it from the new separating velocity
	if (accCausedSeparatingVelocity < 0)
	{
		newSeparatingVelocity += restitution * accCausedSeparatingVelocity;

		// Make sure we haven't removed more that was there to remove
		if (newSeparatingVelocity < 0) newSeparatingVelocity = 0;
	}

	// Get the velocity after contact
	real deltaVelocity = newSeparatingVelocity - separatingVelocity;

	real totalInverseMass = particle[0]->getInverseMass();
	if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

	// No impulse to apply, the two object are stationary
	if (totalInverseMass <= 0) return;

	// Calculate the impulse
	real impulse = deltaVelocity / totalInverseMass;

	// Find the amount of impulse per unit of inverse mass
	Vector3 impulsePerMass = contactNormal * impulse;

	// Apply the impulse in the direction of the contact and proportional to the mass
	particle[0]->setVelocity(particle[0]->getVelocity() + impulsePerMass * particle[0]->getInverseMass());

	if (particle[1])
	{
		// Particle 1 goes in the opposite direction
		particle[1]->setVelocity(particle[1]->getVelocity() + impulsePerMass * -particle[0]->getInverseMass());
	}

}


void ParticleContact::resolveInterpenetration(real duration) {
	if (penetration <= 0) return;

	// The movement for each object is based on its inverse mass, so total that
	real totalInverseMass = particle[0]->getInverseMass();

	if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

	// If both particle have infinite mass, we do nothing
	if (totalInverseMass <= 0) return;
	
	// Find the movement per inverse mass unit
	Vector3 movePerIMass = contactNormal * (-penetration / totalInverseMass);

	// Apply the correction
	particle[0]->setPosition(particle[0]->getPosition() + movePerIMass * particle[0]->getInverseMass());

	if (particle[1]) particle[1]->setPosition(particle[1]->getPosition() + movePerIMass * particle[1]->getInverseMass());

}

ParticleContactResolver::ParticleContactResolver(unsigned iterations) {
	ParticleContactResolver::iterations = iterations;
}

void ParticleContactResolver::setIterations(unsigned iterations) {
	ParticleContactResolver::iterations = iterations;
}

void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned numContacts, real duration) {
	iterationsUsed = 0;

	while (iterationsUsed < iterations)
	{
		// Find the contact with the largest closing velocity
		real max = 0;
		unsigned maxIndex = numContacts;

		for (unsigned i = 0; i < numContacts; i++)
		{
			real sepVel = contactArray[i].calculateSeparatingVelocity();
			if (sepVel < max)
			{
				max = sepVel;
				maxIndex = i;
			}	
		}

		// Resolve the contact
		contactArray[maxIndex].resolve(duration);


		iterationsUsed++;

	}

}