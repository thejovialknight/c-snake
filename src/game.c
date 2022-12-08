#include "game.h"

void update_and_render(struct Game *game, struct Platform *platform, double delta_time) {
	////////////
	// UPDATE //
	////////////
	struct Input *input = &platform->input;

	// Set move from just pressed input
	if(input->w == true && game->previous_input.w == false && 
	    game->direction.y != 1)
	{
		game->next_move.x = 0;
		game->next_move.y = -1;
	}
	if(input->a == true && game->previous_input.a == false &&
	    game->direction.x != 1)
	{
		game->next_move.x = -1;
		game->next_move.y = 0;
	}
	if(input->s == true && game->previous_input.s == false &&
	    game->direction.y != -1)
	{
		game->next_move.x = 0;
		game->next_move.y = 1;
	}
	if(input->d == true && game->previous_input.d == false &&
	    game->direction.x != -1)
	{
		game->next_move.x = 1;
		game->next_move.y = 0;
	}

	// Tick timer
	game->time_to_next_step -= delta_time;
	if(game->time_to_next_step <= 0) {
		game->time_to_next_step = game->step_length;
		step(game);
	}

	game->previous_input.w = input->w;
	game->previous_input.a = input->w;
	game->previous_input.s = input->w;
	game->previous_input.d = input->w;

	////////////
	// Render //
	////////////
	// Draw background
	int pixel_count = platform->win_h * platform->win_w;
	struct Color bg = {0.1, 0.1, 0.1};
	for(int i = 0; i < pixel_count; ++i) {
		platform->pixels[i] = bg; 
	}

	// Draw tiles
	for(int y = 0; y < ROWS; ++y) {
		for(int x = 0; x < COLUMNS; ++x) {
			struct Color color = {0.5, 0.5, 0.5};
			draw_cell(platform, color, x, y);
		}
	}

	// Draw food
	struct Color food_color = {0.75, 0.25, 0.25};
	draw_cell(platform, food_color, game->food.x, game->food.y);

	// Draw snake
	struct Color snake_head_color = {0.25, 0.75, 0.25};
	struct Color snake_color = {0.25, 0.25, 0.75};
	draw_cell(platform, snake_head_color, game->snake[0].x, game->snake[0].y);
	for(int i = 1; i < game->snake_length; ++i) {
		draw_cell(platform, snake_color, game->snake[i].x, game->snake[i].y);
	}
}

void start_game(struct Game *game) {
	game->snake_length = 2;
	struct Coordinate snake_head = {
		COLUMNS / 2,
		ROWS / 2
	};
	game->snake[0] = snake_head;
	game->snake[1] = snake_head;
	game->snake[1].x -= 1;
	game->snake[2] = snake_head;
	game->snake[2].x -= 2;

	struct Coordinate next_move = {1, 0};
	game->next_move = next_move;
	game->direction = game->next_move;

	game->step_length = 0.1;
	game->time_to_next_step = game->step_length;
	
	struct Coordinate food_pos = {4, 4};
	game->food = food_pos;
}

void draw_cell(struct Platform *platform, struct Color color, int x, int y) {
	double tile_gap = 8; 
	double tile_size = 32;
	double left_edge = ((double)platform->win_w / 2) - (((double)COLUMNS / 2) * tile_size) - (((double)COLUMNS / 2) * tile_gap);
	double top_edge = ((double)platform->win_h / 2) - (((double)ROWS / 2) * tile_size) - (((double)ROWS / 2) * tile_gap);
	int rx = left_edge + (x * tile_size) + (x * tile_gap);
	int ry = top_edge + (y * tile_size) + (y * tile_gap);
	int rw = tile_size;
	int rh = tile_size;
	for(int y = ry; y < ry + rh; ++y) {
		for(int x = rx; x < rx + rw; ++x) {
			draw_pixel(platform, color, x, y); 
		}
	}
}

void step(struct Game *game) {
	game->direction = game->next_move;
	struct Coordinate new_snake_head;
	struct Coordinate *snake_head = &game->snake[0];
	new_snake_head.x = snake_head->x + game->next_move.x;
	new_snake_head.y = snake_head->y + game->next_move.y;

	// Check if new position is out of bounds
	if(new_snake_head.x < 0 ||
	   new_snake_head.x >= COLUMNS ||
	   new_snake_head.y < 0 ||
	   new_snake_head.y >= ROWS)
	{
		start_game(game);
		return;
	}

	// Check if new position hits the snake
	for(int i = 0; i < game->snake_length; ++i) {
		if(new_snake_head.x == game->snake[i].x && new_snake_head.y == game->snake[i].y) {
			start_game(game);
			return;
		}
	}

	// Shift all snakes to the right and set i0 to the new position
	for(int i = game->snake_length; i > 0; --i) {
		game->snake[i] = game->snake[i - 1];
	}
	game->snake[0] = new_snake_head;

	// Check if new position is a food
	// Must happen after move or else snake length changes iteration
	if(snake_head->x == game->food.x && snake_head->y == game->food.y) {
		game->snake_length++;
		
		// Move food
		if(game->food.x != 11) {
			game->food.x = 11;
			game->food.y = 13;
		}
		else {
			game->food.x = 4;
			game->food.y = 4;
		}
	}
}

