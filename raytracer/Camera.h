#pragma once
#include "stdafx.h"

class Camera {
public:
	Camera(vec3 position, vec3 up, vec3 front, float FOV, float aspectRatio)
		: position(position), up(up.unit()), front(front.unit()),
		FOV(FOV), aspectRatio(aspectRatio)
	{
		initialize();
	}

	vec3 getUp() { return up; }
	vec3 getRight() { return right; }
	vec3 getFront() { return front; }

	vec3 getPosition() { return position; }

private:
	void initialize() {
		right = front.cross(up);
		right = right.unit();

		up = up/aspectRatio;

		front = front / tan(FOV/2.f);
	}
	vec3 position, up, front, right;
	float FOV;
	float aspectRatio;
};