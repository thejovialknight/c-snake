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
	struct Color *pixels;
};

struct Platform init_platform();
struct Input input_from_platform();
void draw_pixel(struct Platform *platform, struct Color color, int x, int y);
void render(struct Platform *platform);
