#pragma once
#include "stdafx.h"

class vec3
{
public:
	typedef const vec3 i; //input vector

	float x, y, z;

	vec3() { x = y = z = 0.0f; }
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}; 

	vec3 unit() const {
		float length = this->length();
		return vec3(x/length, y/length, z/length);
	}

	float length() const {
		return sqrt(length2());
	}

	float length2() const {
		return (x*x + y*y + z*z);
	}

	float distanceTo(vec3::i a) const {
		return (a-(*this)).length();
	}

	float distanceTo2(vec3::i a) const {
		return (a-(*this)).length2();
	}

	float dot(vec3::i a) const {
		return (x*a.x + y*a.y + z*a.z);
	}

	vec3 cross(vec3::i a) const {
		return vec3(
			y*a.z - a.y*z,
			z*a.x - a.z*x,
			x*a.y - a.x*y
		);
	}

	/** Operators **/
	inline vec3 operator-(vec3::i a) const {
		return (*this) + (-a);
	}

	inline vec3 operator-() const {
		return vec3(-x, -y, -z);
	}

	inline vec3 operator+(vec3::i a) const {
		return vec3(a.x+x, a.y+y, a.z+z);
	}

	inline vec3 operator*(float t) const {
		return vec3(x*t, y*t, z*t);
	}

	inline vec3 operator/(float t) const {
		return (*this)*(1/t);
	}
};