#include "game.h"

void update_and_render(struct Game *game, struct Platform *platform, double delta_time) {
	struct Input *input = &platform->input;

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
	int pixel_count = platform->win_h * platform->win_w;
	struct Color bg = {0.1, 0.1, 0.1};
	for(int i = 0; i < pixel_count; ++i) {
		platform->pixels[i] = bg; 
	}

	double tile_gap = 8; 
	double tile_size = 48;
	double left_edge = ((double)platform->win_w / 2) - (((double)COLUMNS / 2) * tile_size) - (((double)COLUMNS / 2) * tile_gap);
	double top_edge = ((double)platform->win_h / 2) - (((double)ROWS / 2) * tile_size) - (((double)ROWS / 2) * tile_gap);
	// Draw tiles
	for(int y = 0; y < ROWS; ++y) {
		for(int x = 0; x < COLUMNS; ++x) {
			// Calculate tile rect
			int rx = left_edge + (x * tile_size) + (x * tile_gap);
			int ry = top_edge + (y * tile_size) + (y * tile_gap);
			int rw = tile_size;
			int rh = tile_size;
			
		}
	}
}

void step(struct Game *game) {
	// move player
	// - shift all elements to the right up to snake_length and make i0 new pos
	// check if player ran into edge or themself and die 
	// check if player ran into food, if so, iterate snake_length
}
