#include "Background.hpp"

Background::Background(void) : GameObject() {
	ByteColorImage* image = AssetManager::getByteColor("tile");

	tile.colors = image->data;
	tile.size.width = image->width;
	tile.size.height = image->height;

	tile_draw_rect.x = 0;
	tile_draw_rect.y = 0;
	tile_draw_rect.width = tile.size.width;
	tile_draw_rect.height = tile.size.height;

	fill_color = Color::aqua;

	tile_velocity_x = config::game::bg_velocity;

	tiles_start_y = config::screen::height - tile.size.height;

	tiles_start_x = 0;
}

void Background::draw(void) {
	// Fill the background with a solid color.
	Console::getInstance()->draw(fill_color, config::screen::width, config::screen::height);
	
	Rect2d screen_rect = { 0, tiles_start_y, tile.size.width, tile.size.height };

	// Get the tile width.
	const double tile_w = static_cast<double>(tile.size.width);

	// Draw tiles until fill the screen along the X axis.
	for (double x = tiles_start_x; x < config::screen::width; x += tile_w) {
		screen_rect.x = x;

		Console::getInstance()->draw(tile, tile_draw_rect, screen_rect);
	}
}

void Background::update(double delta_time) {
	// Skip update if tile velocity is zero.
	if (tile_velocity_x == 0) {
		return;
	}

	// Update tiles start position on the X axis.
	tiles_start_x += tile_velocity_x * delta_time;

	// Get the tile width.
	const double tile_w = static_cast<double>(tile.size.width);

	if (tiles_start_x <= -tile_w) {
		tiles_start_x -= tile_w;
	}
}

void Background::stop(void) {
	tile_velocity_x = 0;
}

void Background::start(void) {
	tile_velocity_x = config::game::bg_velocity;
}