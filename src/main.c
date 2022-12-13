#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "SDL_render.h"
#include "SDL_video.h"
#include "platform.h"
#include "game.h"

int main(int argc, char* argv[]) {
	printf("Program start!");
	struct Platform platform = init_platform();
	struct Game game;
	start_game(&game);

	int pixel_count = platform.win_w * platform.win_h;

	// Seed random number generator
	srand(time(NULL));

	// Set initial marker for deltaTime which is used to keep track of frame lengths for the
	// purpose of framerate independent simulation of time dependent behaviors.
	Uint32 ticks_count = 0;

	bool quit = false;
	while(!quit) {
		// Set the current deltaTime for the frame
		double delta_time = (SDL_GetTicks() - ticks_count) / 1000.0f;
		ticks_count = SDL_GetTicks();
		printf("delta_time: %f\n", delta_time);

		// Make sure delta time doesn't exceed a certain value. This is
		// to prevent serious issues from occuring as a result of lag or
		// using debug break points.
		if(delta_time > 0.05) {
			delta_time = 0.05;
		}
		platform.input = input_from_platform();
		update_and_render(&game, &platform, delta_time);
		render(&platform);
		quit = platform.input.quit;
	}
	SDL_DestroyWindow(platform.window);
	SDL_DestroyRenderer(platform.renderer);
	SDL_DestroyTexture(platform.texture);
	return 0;
}
