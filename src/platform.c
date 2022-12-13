#include "platform.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include <stdio.h>

struct Platform init_platform() {
	struct Platform platform;
	SDL_Init(SDL_INIT_EVERYTHING);
	platform.win_w = 2560;
	platform.win_h = 1440; 
	platform.window = SDL_CreateWindow("cnake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, platform.win_w, platform.win_h, SDL_WINDOW_FULLSCREEN);
	platform.renderer = SDL_CreateRenderer(platform.window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetWindowMinimumSize(platform.window, platform.win_w, platform.win_h);
	SDL_RenderSetLogicalSize(platform.renderer, platform.win_w, platform.win_h);
	SDL_RenderSetIntegerScale(platform.renderer, 1);
	platform.texture = SDL_CreateTexture(platform.renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, platform.win_w, platform.win_h);
	platform.pixels = malloc(platform.win_w * platform.win_h * 4);
	return platform;
}

struct Input input_from_platform() {
	struct Input input;
	input.w = false;
	input.a = false;
	input.s = false;
	input.d = false;
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
				case SDLK_ESCAPE:
					input.quit = true;
					break;
				default:
					break;
			}
		}
	}

	return input;
}

void draw_pixel(struct Platform *platform, struct Color *color, int x, int y) {
	int index = x + y * platform->win_w;
	buffer_pixel(platform, color, index);
}

void fill_texture(struct Platform *platform, struct Color *color) {
	int pixel_count = platform->win_w * platform->win_h;
	for(int i = 0; i < pixel_count; ++i) {
		buffer_pixel(platform, color, i);
	}
}

void buffer_pixel(struct Platform *platform, struct Color *color, int index) {
	platform->pixels[index] = color->value;
}

void render(struct Platform *platform) {
	int pitch = platform->win_w * 4;
	SDL_LockTexture(platform->texture, NULL, (void**) &platform->pixels, &pitch);
	/* Set every pixel to white.
	for (int y = 0; y < platform->win_h; ++y)
	{
		for (int x = 0; x < platform->win_w; ++x)
		{
			SDL_PixelFormat pixel_format;
			pixel_format.format = SDL_PIXELFORMAT_RGBA32;
			struct Color color = {10, 70, 0, 255};
			platform->pixels[x + y * platform->win_w] = color.value;
			//platform->pixels[x + y * platform->win_w] = SDL_MapRGBA(&pixel_format, 255, 0, 0, 255);
			//platform->pixels[x + y * platform->win_w] = 0xffffffff;
		}
	}
	//*/
	printf("Rendering...\n");
	SDL_SetRenderDrawColor(platform->renderer, 0, 10, 0, 255);
	SDL_RenderClear(platform->renderer);
	//SDL_UpdateTexture(platform->texture, NULL, platform->pixels, platform->win_w * 4);
	SDL_UnlockTexture(platform->texture);
	SDL_RenderCopy(platform->renderer, platform->texture, NULL, NULL);
	SDL_RenderPresent(platform->renderer);
	printf("Render complete!\n");
}
