#pragma once
#include "stdafx.h"

class Object {
public:
	vec3 position;
	Material *material;

	Object(vec3 position, Material *material) : position(position), material(material) {}

	virtual float intersect(Ray r) =0;
	virtual vec3 normal(vec3::i point) =0;
};

class Sphere : public Object {
public:
	float radius;

	Sphere(vec3 position, float radius, Material *material) : Object(position, material), radius(radius) {}

	virtual vec3 normal(vec3::i p) {
		return (p-position) / radius;
	}

	virtual float intersect(Ray r) {
		vec3 v = r.origin - position;
		float b = v.dot(r.head);
		if(b > 0) { return undefined; }
		float delta2 = b*b - v.dot(v) + radius*radius;
		
		if(delta2 < 0.f) { return undefined; }
		
		float delta = sqrt(delta2);
		float t1 = -b-delta;
		float t2 = -b+delta;
		if(t1 > epsilon) { return t1; }
		if(t2 > epsilon) { return t2; }
		return undefined;
	}
};