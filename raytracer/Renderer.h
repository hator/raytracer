#pragma once
#include "stdafx.h"
#include "Scene.h"
#include "Camera.h"

class Renderer {
public:
	Renderer(Camera& camera, Scene& scene) : camera(camera), s(scene) {}

	void render(ColorRGB* buffer, int width, int height, int maxDepth, int samplesPerPixel) {
		for(int y=0; y < height; y++) {
			for(int x=0; x < width; x++) {
				buffer[y*width+x] = ColorRGB(samplePixel(x, y, width, height, maxDepth, samplesPerPixel));
			}
		}
	}

private:
	Color samplePixel(int x, int y, int width, int height, int maxDepth, int samplesPerPixel) {
		Ray ray;
		Color color = Color::black;
		for(int i=0; i < samplesPerPixel; i++) {
			ray = primRay(x + 0.5f - uRand(), y + 0.5f - uRand(), width, height);
			color = color + trace(s, ray);
		}
		return color/fl(samplesPerPixel);
	}


	Ray primRay(float x, float y, int width, int height) {
		float Ax = 2.f*x/fl(width) - 1.f;
		float Ay = 2.f*y/fl(height) - 1.f;

		vec3 head = camera.getFront() + camera.getRight()*Ax + camera.getUp()*Ay;
		head = head.unit();

		return Ray(camera.getPosition(), head);
	}
	

	Color trace(Scene& scene, Ray& ray) {
		Hit hit = scene.castRay(ray);
		if(hit.distance == infinity) {
			return scene.getAmbientLight();
		}

		vec3 normal = hit.normal;


		return Color::red * lambert(scene, hit);
	}


	Color lambert(Scene& scene, Hit& hit) {
		vec3 toLight = hit.point - scene.getLight().position;
		vec3 toLightDir = toLight.unit();
		float cosNL = hit.normal.dot(toLightDir);
		if(cosNL < 0.f) { return scene.getAmbientLight(); }
		float d2 = scene.getLight().position.distanceTo2(hit.point);
		Ray shadowRay(hit.point, toLightDir);
		Hit obstacle = scene.castRay(shadowRay);
		if(obstacle.distance*obstacle.distance < d2) {
			return scene.getAmbientLight();
		} else {
			return scene.getAmbientLight()+scene.getLight().brightness*cosNL;
		}


		return Color::white;
	}


	Camera& camera;
	Scene& s;
};