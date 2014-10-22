#include "stdafx.h"
#include "Quaternion.h"
#include "Color.h"
#include "Hit.h"
#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"
#include <thread>

#define NUM_THREADS 4

int main(int argc, char* argv[]) {
	int width = 640;
	int height = 480;
	
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) != 0) {
		fprintf(stderr, "SDL error: %s\n", SDL_GetError());
		getchar();
		SDL_Quit();
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if(window == nullptr) {
		fprintf(stderr, "SDL error: %s\n", SDL_GetError());
		getchar();
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 2;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, width, height);
	/**************************/


	ColorRGB* buffer = new ColorRGB[width*height];

	Scene scene;
	Camera camera(vec3(0, 0, 0), vec3(0, 1.f, 0), vec3(0, 0, 1.f), Pi/2.f, fl(width)/height);

	std::thread threads[NUM_THREADS];
	int oneChunkHeight = height / NUM_THREADS;
	int startY = 0;
	Renderer r(camera, scene);
	for(int i = 0; i < NUM_THREADS; i++) {
		threads[i] = std::thread([=, &r]() {
			r.render(buffer, startY, startY + oneChunkHeight, width, height, 5, 100);
		});
		startY += oneChunkHeight;
	}

	/**************************/
	SDL_Event e;
	bool quit = false;
	while(!quit) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDL_UpdateTexture(texture, nullptr, buffer, width*sizeof(ColorRGB));

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}

	delete [] buffer;

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

