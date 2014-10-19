#pragma once
#include "stdafx.h"
#include "Scene.h"
#include "Camera.h"

class Renderer {
public:
	Renderer(Camera& camera, Scene& scene) : camera(camera), scene(scene) {}

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
			color = color + trace(ray, maxDepth);
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
	

	Color trace(Ray& ray, int depth) {
		Hit hit = scene.castRay(ray);
		if(hit.distance == infinity) {
			return scene.getAmbientLight();
		}

		Color refraction = hit.obj->material->refraction;
		
		if(depth > 0) {
			if(refraction!=Color::black) {
				refraction = refraction * trace(refract(ray, hit), depth-1);
			}
		}

		return refraction + hit.obj->material->diffuse* lambert(hit);
	}

	Ray refract(Ray& ray, Hit& hit) {
		float ior = hit.obj->material->indexOfRefraction;
		float d = hit.normal.dot(-ray.head);
		float ir, a;
		if( d < 0.f) {
			ir = ior;
			a = -1.f;
			d *= -1.f;
		} else {
			ir = 1.f/ior;
			a = 1.f;
		}

		float i = 1.f - ir*ir*(1.f - d*d);
		vec3 head = hit.normal*a*(ir*d - sqrt(i)) - (-ray.head)*ir;

		return Ray(hit.point, head.unit());
	}


	Color lambert(Hit& hit) {
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
	}


	Camera& camera;
	Scene& scene;
};