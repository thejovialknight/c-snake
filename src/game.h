#pragma once
#include <stdbool.h>
#include "color.h"
#include "platform.h"

#define ROWS 16
#define COLUMNS 16
#define MAX_SNAKE_LENGTH 128

struct Coordinate {
	int x;
	int y;
};

struct Game {
	struct Color tiles[ROWS][COLUMNS];
	struct Coordinate food;
	struct Coordinate snake[MAX_SNAKE_LENGTH];
	struct Coordinate direction;
	int snake_length;
	double step_length;
	double time_to_next_step;
	struct Input previous_input;
	struct Coordinate next_move;
};

void update_and_render(struct Game *game, struct Platform *platform, double delta_time);
void start_game(struct Game *game);
void draw_cell(struct Platform *platform, struct Color color, int x, int y);
void step(struct Game *game);
