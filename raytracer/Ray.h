#pragma once
#include "stdafx.h"

class Ray {
public: 
	typedef const Ray i; //input ray

	vec3 origin, head;
	
	Ray() {}
	Ray(vec3 origin, vec3 head) : origin(origin), head(head) {};
};
