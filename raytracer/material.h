#pragma once
#include "stdafx.h"
#include "Color.h"

class Material {
public: 
	Color diffuse;
	Color reflection;
	Color refraction;
	float indexOfRefraction; //index of refraction
	
	Material(
		Color diffuse = Color::black,
		Color reflection = Color::black,
		Color refraction = Color::black,
		float indexOfRefraction = 1.f) 
			: diffuse(diffuse), reflection(reflection),
				refraction(refraction),
				indexOfRefraction(indexOfRefraction)
	{ }

};
