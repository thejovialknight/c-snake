#include "platform.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_video.h"

struct Platform init_platform() {
	struct Platform platform;
	SDL_Init(SDL_INIT_EVERYTHING);
	platform.win_w = 1280;
	platform.win_h = 720; 
	platform.window = SDL_CreateWindow("cnake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, platform.win_w, platform.win_h, SDL_WINDOW_SHOWN);
	platform.renderer = SDL_CreateRenderer(platform.window, -1, SDL_RENDERER_ACCELERATED);
	return platform;
}

struct Input input_from_platform() {
	struct Input input;
	SDL_Event event;
	while(SDL_PollEvent(&event) != 0) {
		if(event.type == SDL_QUIT) {
			input.quit = true;
		}
		
		if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
				case SDLK_w:
					input.w = true;
					break;
				case SDLK_a:
					input.a = true;
					break;
				case SDLK_s:
					input.s = true;
					break;
				case SDLK_d:
					input.d = true;
					break;
				default:
					break;
			}
		}
	}

	return input;
}

void render(struct Platform *platform) {
	SDL_SetRenderDrawColor(platform->renderer, 0, 0, 0, 255);
	SDL_RenderClear(platform->renderer);
	for(int i = 0; i < platform->win_w * platform->win_h; ++i) {
		int y = i / platform->win_w;
		int x = i - y * platform->win_w;
		struct Color *color = &platform->pixels[i];
		SDL_SetRenderDrawColor(platform->renderer, color->r * 255, color->g * 255, color->b * 255, 255);
		SDL_RenderDrawPoint(platform->renderer, x, y);
	}
	SDL_RenderPresent(platform->renderer);
}
