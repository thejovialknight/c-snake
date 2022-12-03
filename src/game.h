#pragma once
#include "color.h"
#include "platform.h"

struct Game {
	double tick;
};

void update_and_render(struct Game *game, struct PlatformInput input, struct Color *out_colors, int pixel_count);
