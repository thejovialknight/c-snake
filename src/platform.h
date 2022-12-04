#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "color.h"

struct Input {
	bool w;
	bool a;
	bool s;
	bool d;
	bool quit;
};

struct Platform {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int win_w;
	int win_h;
	struct Input input;
};

struct Platform init_platform();
struct Input input_from_platform();
void render_to_platform(struct Color colors[], struct Platform *platform);
 
