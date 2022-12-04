#include "game.h"

void update_and_render(struct Game *game, struct Input *input, struct Color *out_colors, int pixel_count, double delta_time) {
	// Set move from just pressed input
	if(input->w == true && game->previous_input.w == false) {
		game->next_move.x = 0;
		game->next_move.y = 1;
	}
	if(input->a == true && game->previous_input.a == false) {
		game->next_move.x = -1;
		game->next_move.y = 0;
	}
	if(input->s == true && game->previous_input.s == false) {
		game->next_move.x = 0;
		game->next_move.y = -1;
	}
	if(input->d == true && game->previous_input.d == false) {
		game->next_move.x = 1;
		game->next_move.y = 0;
	}

	// Tick timer
	game->time_to_next_step -= delta_time;
	if(game->time_to_next_step <= 0) {
		game->time_to_next_step = game->step_length;
		step(game);
	}

	// Render
	// Draw background
	struct Color bg = {0.1, 0.1, 0.1};
	for(int i = 0; i < pixel_count; ++i) {
		out_colors[i] = bg; 
	}
	// Draw tiles
	for(int y = 0; y < HEIGHT; ++y) {
		for(int x = 0; x < WIDTH; ++x) {
			// Calculate tile rect
			int rx;
			int ry;
			int rw;
			int rh;

			// Draw rect
		}
	}
}

void step(struct Game *game) {
	// move player
	// - shift all elements to the right up to snake_length and make i0 new pos
	// check if player ran into edge or themself and die 
	// check if player ran into food, if so, iterate snake_length
}
