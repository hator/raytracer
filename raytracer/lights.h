#pragma once
#include "stdafx.h"

class Light {
public:
	Color brightness;
	Color ambient;
	vec3 position;

	Light(vec3 position, Color brightness, Color ambient) 
		: position(position), brightness(brightness), ambient(ambient)
	{}

	Light(vec3 position, Color brightness)
		: position(position), brightness(brightness), ambient(brightness*0.2f)
	{}
};