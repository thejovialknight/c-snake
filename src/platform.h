#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "color.h"

struct PlatformInput {
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
	struct PlatformInput input;
};

struct Platform init_platform();
struct PlatformInput input_from_platform();
void render_to_platform(struct Color colors[], struct Platform *platform);
 
