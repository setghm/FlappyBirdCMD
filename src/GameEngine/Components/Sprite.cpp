#include "Sprite.hpp"

#include "../Console.hpp"

Sprite::Sprite() {
	size = { 0 };
	velocity = { 0 };
	world_bounds = { 0 };
	flipped_x = false;
	flipped_y = false;
}

Sprite::Sprite(ByteColorImage* bytecolor) : Sprite() {
	size.height = bytecolor->height;
	size.width = bytecolor->width;
	data = bytecolor->data;
}

void Sprite::update(double delta_time) {
	PhysicsObject::update(delta_time);

	const bool world_bounds_active = world_bounds.width > 0 && world_bounds.height > 0;
	
	if (world_bounds_active) {
		// Set velocity to 0 if the position is in the world bounds limit
		// and restore the x or y positions.
		
		if (velocity.x != 0) {
			const double max_x = world_bounds.x + world_bounds.width;

			const bool greater_x = position.x + size.width > max_x;
			const bool lower_x = position.x < world_bounds.x;

			if (greater_x || lower_x) {
				velocity.x = 0;
				position.x = greater_x ? max_x - size.width : world_bounds.x;
			}
		}

		if (velocity.y != 0) {
			const double max_y = world_bounds.y + world_bounds.height;

			const bool greater_y = position.y + size.height > max_y;
			const bool lower_y = position.y < world_bounds.y;

			if (greater_y || lower_y) {
				velocity.y = 0;
				position.y = greater_y ? max_y - size.height : world_bounds.y;
			}
		}
	}
}

void Sprite::draw(void) {
	const double w = static_cast<double>(size.width);
	const double h = static_cast<double>(size.height);

	const Rect2d data_rect { 0, 0, w, h };

	const Rect2d screen_rect {
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		flipped_x ? -w : w,
		flipped_y ? -h : h
	};

	Console::getInstance()->draw(data, data_rect, screen_rect);
}
