#pragma once
#include <include/particle.h>
#include <include/pcontacts.h>


namespace cyclone {

	/*
	* Links connects two particle together, generating a contact if they violate
	* the constraints of their link. It is used as a base class for cables and rods, and could
	* be used as a base class for spring with a limit to their extension.
	*/
	class ParticleLink
	{
	public:
		/*
		* Holds the pair of particle that are connected by this link
		*/
		Particle* particle[2];

	protected:
		/*
		* Returns the current length of the cable.
		*/
		real currentLength() const;

	public:
		/*
		* Fills the given contact structure with the contact needed
		* to keep the link from violating its constraint.The contact
		* pointer should point to the first available contact in a
		* contact array, where limit is the maximum number of
		* contacts in the array that can be written to.The method
		* returns the number of contacts that have been written.This
		* format is common to contact - generating functions, but this
		* class can only generate a single contact, so the
		* pointer can be a pointer to a single element. The limit
		* parameter is assumed to be at least one (zero isn’t valid),
		* and the return value is either 0, if the cable wasn’t
		* overextended, or one if a contact was needed.
		*/
		virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const = 0;

	};

	/*
	* Cable links a pair of particle, generating a contact if they stray too far apart
	*/
	class ParticleCable : public ParticleLink
	{
	public:
		/*
		* Holds the max length of the cable
		*/
		real maxLength;

		/*
		* Holds the restitution of the cable (bounciness)
		*/
		real restitution;

		/*
		* Fills the given contact structure with the contact need to keep the cable from overextending
		*/
		virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const;

	};

	/*
	* Rods links a pair of particle, generating a contact if they stray too far apart
	* or if they get too close
	*/
	class ParticleRod : public ParticleLink

	{
	public:
		/*
		* Holds the length of the rod
		*/
		real length;

		/*
		* Returns the current length of the rod
		*/
		real currentLength() const;

		/*
		* Fills the given structure with the contact needed to keep the rod from extending or compressing
		*/
		virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const;
		

	private:

	};

}