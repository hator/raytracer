#pragma once
#include "stdafx.h"

class Quaternion {
public:
	float w;
	vec3 v;

	Quaternion(float w, float x, float y, float z);
	Quaternion(float w, vec3 v);
	Quaternion(vec3 axis, float angle);

	static Quaternion fromTwoVectors(vec3::i u, vec3::i v);

	Quaternion inverse() const;
	Quaternion operator*(const Quaternion q) const;
	vec3 rotate(vec3::i p) const;
};

vec3 rotate(vec3::i v, const Quaternion q);