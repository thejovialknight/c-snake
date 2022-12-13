#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "color.h"
#include "platform.h"

#define ROWS 12
#define COLUMNS 12

struct Coordinate {
	int x;
	int y;
};

enum GameState {
	GAME_INTERSTITIAL,
	GAME_RUNNING
};

struct BoardOrientation {
	int tile_gap;
	int tile_size;
	int left_edge;
	int top_edge;
};

struct Game {
	enum GameState state; 
	struct Color tiles[ROWS][COLUMNS];
	struct Coordinate food;
	struct Coordinate snake[ROWS * COLUMNS];
	struct Coordinate direction;
	int snake_length;
	double step_length;
	double time_to_next_step;
	struct Input previous_input;
	struct Coordinate next_move;
	struct Coordinate countdown_coordinate;
	struct BoardOrientation orientation;
};

void update_and_render(struct Game *game, struct Platform *platform, double delta_time);
void update_interstitial(struct Game *game, struct Platform *platform, double delta_time);
void update_running(struct Game *game, struct Platform *platform, double delta_time);
void step(struct Game *game);
void start_game(struct Game *game);
void draw_background_and_tiles(struct Platform *platform, struct BoardOrientation *orientation);
void draw_cell(struct Platform *platform, struct BoardOrientation *orientation, struct Color *color, int x, int y);
struct BoardOrientation get_board_orientation(struct Platform *platform);
void move_food(struct Game *game);
