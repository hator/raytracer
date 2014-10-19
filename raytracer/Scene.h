#pragma once
#include "stdafx.h"
#include "Hit.h"

class Scene {
	std::vector<Object*> objects;
	Light light;

public:
	Scene() : light(Light(vec3(0.f, 2.f, 2.f), Color::yellow)) {
		Material *blueStone = new Material(Color::blue);
		Material *redStone = new Material(Color::red);
		Material *yellowStone = new Material(Color::yellow);
		Material *glass = new Material(Color::black, Color::gray, Color(0.95f, 0.95f, 0.95f), 1.46f);

		objects.push_back(new Sphere(vec3(0, 0, 1.5f), 0.5f, redStone));
		objects.push_back(new Sphere(vec3(0.1f, 0.1f, 0.4f), 0.1f, glass));
		//objects.push_back(new Sphere(vec3(0, 0.5f, 0), 0.5f, yellowStone));
		//objects.push_back(new Sphere(vec3(-0.3f, 0.65f, 0.8f), 0.2f, glass));
		//objects.push_back(new Sphere(vec3(0.3f, 0.45f, 0.8f), 0.2f, glass));
	}
	
	Hit castRay(Ray r) {
		float nearest = undefined;
		Object* o = nullptr;
		for(auto it = objects.begin(); it != objects.end(); it++) {
			float t = (*it)->intersect(r);
			if(t<nearest) {
				nearest = t;
				o = *it;
			}
		}

		if(nearest != infinity) {
			return Hit(o, nearest, r);
		}
		return Hit();
	}

	Color getAmbientLight() {
		//for(light in lights) { ambient+=light.ambient }
		return Color::darkBlue;
	}

	Light getLight() {
		return light;
	}

private:

};