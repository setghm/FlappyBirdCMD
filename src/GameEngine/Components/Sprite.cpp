#include "Sprite.hpp"

#include "../Console.hpp"

#include <cmath>

Sprite::Sprite() : Image() {
	world_bounds = { 0 };
	flipped_x = false;
	flipped_y = false;
	collision_ignore_color_key = false;
}

Sprite::Sprite(ByteColorImage* bytecolor) : Image(bytecolor) {
	world_bounds = { 0 };
	flipped_x = false;
	flipped_y = false;
	collision_ignore_color_key = false;
}

void Sprite::update(double delta_time) {
	// Update the position.
	body.updatePosition(delta_time, position);

	const bool world_bounds_active = world_bounds.width > 0 && world_bounds.height > 0;
	
	if (world_bounds_active) {
		// Set velocity to 0 if the position is in the world bounds limit
		// and restore the x or y positions.
		
		if (body.getVelocityX() != 0) {
			const double width = getWidth();
			const double max_x = world_bounds.x + world_bounds.width;

			const bool greater_x = position.x + width > max_x;
			const bool lower_x = position.x < world_bounds.x;

			if (greater_x || lower_x) {
				body.setVelocityX(0);
				position.x = greater_x ? max_x - width : world_bounds.x;
			}
		}

		if (body.getVelocityY() != 0) {
			const double height = getHeight();
			const double max_y = world_bounds.y + world_bounds.height;

			const bool greater_y = position.y + height > max_y;
			const bool lower_y = position.y < world_bounds.y;

			if (greater_y || lower_y) {
				body.setVelocityY(0);
				position.y = greater_y ? max_y - height : world_bounds.y;
			}
		}
	}
}

bool Sprite::checkCollision(Sprite* other) {
	// Get edges.
	const double tl = left(); // This left
	const double tg = right(); // This right
	const double tt = top(); // This top
	const double tb = bottom(); // This bottom
	const double ol = other->left(); // Other left
	const double og = other->right(); // Other right
	const double ot = other->top(); // Other top
	const double ob = other->bottom(); // Other bottom

	// Check if the other area is overlapping this area or visceversa.
	bool ovx = (tl >= ol && tl <= og) || (tg >= ol && tg <= og);
	bool ovy = (tt >= ot && tt <= ob) || (tb >= ot && tb <= ob);

	if (ovx && ovy) {
		// Check if color keys are ignored on collisions.
		const bool ocki = other->collision_ignore_color_key; // Other color key ignoring
		const bool tcki = collision_ignore_color_key; // This color key ignoring

		if (ocki || tcki) {
			const uint8_t ock = static_cast<uint8_t>(other->getData().color_key); // Other color key
			const uint8_t tck = static_cast<uint8_t>(data.color_key); // This color key
			const auto& od = other->getData().colors; // Other data
			const auto& td = data.colors; // This data

			// Get collision area from this and the other sprite.
			const double x0 = tl > ol ? tl : ol;
			const double x1 = tg < og ? tg : og;
			const double y0 = tt > ot ? tt : ot;
			const double y1 = tb < ob ? tb : ob;

			// Get this sprite width and other sprite width.
			const double tw = getWidth(); // This width
			const double ow = other->getWidth(); // Other width

			// Iterate over the other sprite and this sprite data arrays.
			for (int y = y0; y < y1; y++) {
				for (int x = x0; x < x1; x++) {

					// Calculate relative coordinates.
					const int tdx = x - tl; // This data X
					const int tdy = y - tt; // This data Y
					const int odx = x - ol; // Other data X
					const int ody = y - ot; // Other data Y

					// Get color.
					const uint8_t tc = td[tdx + tdy * tw]; // This color
					const uint8_t oc = od[odx + ody * ow]; // Other color

					if (tc != tck && oc != ock) {
						return true; // Color overlapping found.
					}

				}
			}

			return false; // No color overlapping found.
		}

		return true;
	}

	return false;
}