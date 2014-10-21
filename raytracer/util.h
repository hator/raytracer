#pragma once
#include "stdafx.h"

#define fl(x) (static_cast<float>(x)) // cast to float

typedef std::numeric_limits<float> real;
const float epsilon = real::epsilon();
const float infinity = real::infinity();
const float undefined = real::infinity();
const float Pi = fl(M_PI);

inline float uRand() { return fl(rand()) / fl(RAND_MAX); }

inline float clamp(float min, float x, float max) {
	return x<min? min : (x>max? max : x);
}

inline float degToRad(float deg) {
	return deg*Pi/180.f;
}
