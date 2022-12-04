#pragma once
#include <stdbool.h>
#include "color.h"
#include "platform.h"

#define WIDTH 16
#define HEIGHT 16
#define MAX_SNAKE_LENGTH 128

struct Coordinate {
	int x;
	int y;
};

struct Game {
	struct Color tiles[HEIGHT][WIDTH];
	struct Coordinate snake[MAX_SNAKE_LENGTH];
	int snake_length;
	double step_length;
	double time_to_next_step;
	struct Input previous_input;
	struct Coordinate next_move;
};

void update_and_render(struct Game *game, struct Input *input, struct Color *out_colors, int pixel_count, double delta_time);
void step(struct Game *game);
