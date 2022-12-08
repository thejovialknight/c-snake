#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "platform.h"
#include "game.h"

int main(int argc, char* argv[]) {
	printf("Program start!");
	struct Platform platform = init_platform();
	struct Game game;
	start_game(&game);

	int pixel_count = platform.win_w * platform.win_h;
	platform.pixels = (struct Color*)malloc(pixel_count * sizeof(struct Color)) ;

	bool quit = false;
	while(!quit) {
		platform.input = input_from_platform();
		update_and_render(&game, &platform, 0.033);
		render(&platform);
		quit = platform.input.quit;
	}
	return 0;
}
