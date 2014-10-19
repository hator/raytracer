#pragma once
#include "stdafx.h"

class Hit {
public:
	vec3 point;
	vec3 normal;
	float distance; // distance from origin to point squared
	Object* obj;

	Hit() : obj(nullptr), distance(undefined) {}
	Hit(Object* o, float d, Ray::i r) : distance(d), obj(nullptr) {
		if(d == undefined) { return; }
		point = r.origin + r.head * d;
		obj = o;
		normal = o->normal(point);
		// materials
	}
};