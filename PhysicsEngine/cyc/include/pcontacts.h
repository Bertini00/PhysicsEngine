#pragma once
#include "particle.h"	

namespace cyclone
{
	/*
	* A contact represents two object in contact (in this case
	* ParticleContact representing two particle). Resolving a contact
	* removes their interpenetration and applies an impulse strong
	* enough to keep them apart. Colliding bodies may also rebound.
	* 
	* The contact has no collable function, to resolve a contact use
	* the contact resolver class
	*/
	class ParticleContact
	{
	public:
		/*
		* Holds the particle that are involved in the contact. The 
		* second of these can be NULL for contact with scenery
		*/
		Particle* particle[2];

		/*
		* Holds the normal restituion of the contact
		*/
		real restitution;

		/*
		* Holds the direction of the contact in world coordinates
		*/
		Vector3 contactNormal;

		/*
		* Holds the depth of penetration at the contact
		*/
		real penetration;

	protected:
		/*
		* Resolves the contact, for both velocity and interpenetration
		*/
		void resolve(real duration);

		/*
		* Calculate the separating velocity at this contact
		*/
		real calculateSeparatingVelocity() const;

	private:
		/*
		* Handles the impulse calculation for this collision
		*/
		void resolveVelocity(real duration);

		/*
		* Handles the interpenetration resolution for this contact
		*/
		void resolveInterpenetration(real duration);
	};


}