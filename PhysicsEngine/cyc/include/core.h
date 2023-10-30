#pragma once
#include "precision.h"
#include <math.h>

namespace cyclone
{
	/**
	* Holds a vector in 3 dimensions. Four data members are allocated
	* to ensure alignment in an array.
	*/
	class Vector3 {

		//Public variable
	public:

		/* Hold the real value of the x axis */
		real x;

		/* Hold the real value of the y axis */
		real y;

		/* Hold the real value of the z axis */
		real z;

		//Private variable
	private:

		/** Padding to ensure 4-word alignment*/
		real pad;


		//Public methods
	public:
		/**
		* The default constructor initializes each value to zero
		*/
		Vector3() : x(0), y(0), z(0) {}

		/**
		* The explicit constructor initializes the vector with the values in input
		*/
		Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}

		/** Adds the given vector to this*/
		void operator+=(const Vector3& vector) {
			x += vector.x;
			y += vector.y;
			z += vector.z;
		}

		/** Returns the value of the given vector added to this*/
		Vector3 operator+(const Vector3& vector) const{
			return Vector3(x + vector.x, y + vector.y, z + vector.z);
		}


		/** Removes the given vector to this*/
		void operator-=(const Vector3& vector) {
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
		}

		/** Return the value of the given vector subtracted to this*/
		Vector3 operator-(const Vector3& vector) const {
			return Vector3(x - vector.x, y - vector.y, z - vector.z);
		}
		
		
		/** Multiplies this vector by the given scalar */
		void operator*=(const real value) {
			x *= value;
			y *= value;
			z *= value;
		}

		/** Returns a copy of this vector scaled to the given scalar */
		Vector3 operator*(const real value) const{
			return Vector3(x * value, y * value, z * value);
		}

		/** Calculate the scalar product between this vector and the given vector*/
		real operator* (const Vector3& vector) const {
			return x * vector.x + y * vector.y + z * vector.z;
		}




		/**
		* Flips all the components of the vector
		*/
		void invert() {
			x = -x;
			y = -y;
			z = -z;

		}

		/** Get the magnitude of the vector*/
		real magnitude() const {
			return real_sqrt(x * x + y * y + z * z);
		}

		/** Get the squared magnitude of the vector */
		real squareMagnitude() const {
			return x * x + y * y + z * z;
		}

		/** Turn a non-zero vector into a vector of unit length*/
		void normalize() {
			real l = magnitude();
			if (l > 0)
				(*this) *= ((real)1) / 1;
		}

		/** Add the given vector to this, scaled by the given amount*/
		void addScaledVector(const Vector3& vector, real scale) {
			x += vector.x * scale;
			y += vector.y * scale;
			z += vector.z * scale;
		}

		/** Calculates and returns the component-wise product of this vector with the given vector*/
		Vector3 componentProduct(const Vector3& vector) const{
			return Vector3(x * vector.x, y * vector.y, z * vector.z);
		}

		/** Calculate the component-wise product of this vector with the given vector 
		* and sets this vector to its result
		*/
		void componentProductUpdate(const Vector3& vector) {
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
		}

		/** Calculate the scalar product between this vector and the given vector*/
		real scalarProduct(const Vector3& vector) const {
			return x * vector.x + y * vector.y + z * vector.z;
		}

		/*
		* Calculate and returns the vector product of this vector with the given vector
		*/
		Vector3 vectorProduct(const Vector3& vector) const {
			return Vector3(
				y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x
			);
		}

		/*
		* Updates this vector to be the vector product between this and the given vector
		*/
		void operator%=(const Vector3& vector) {
			*this = vectorProduct(vector);
		}

		/*
		* Calculates and return the vector product of this vector with the given vector
		*/
		Vector3 operator%(const Vector3& vector) const {
			return Vector3(
				y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x
			);
		}

		/*
		* Zeroes all the components of the vector
		*/
		void clear() {
			x = y = z = 0;
		}
	};
}