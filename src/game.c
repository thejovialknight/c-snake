#include "game.h"

void update_and_render(struct Game *game, struct PlatformInput input, struct Color *out_colors, int pixel_count) {
	game->tick += 0.06;
	if(game->tick >= 0.98) { game->tick = 0; }
	for(int i = 0; i < pixel_count; ++i) {
		struct Color color = {game->tick, game->tick, game->tick};
		out_colors[i] = color; 
	}
}
