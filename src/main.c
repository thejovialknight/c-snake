#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "platform.h"
#include "game.h"

int main(int argc, char* argv[]) {
	struct Platform platform = init_platform();
	struct Game game;
	game.tick = 0;

	int pixel_count = platform.win_w * platform.win_h;
	struct Color *colors = (struct Color*)malloc(pixel_count * sizeof(struct Color)) ;

	bool quit = false;
	while(!quit) {
		struct PlatformInput input = input_from_platform();
		update_and_render(&game, input, &colors[0], pixel_count);
		render_to_platform(colors, &platform);
		quit = input.quit;
	}
	return 0;
}
