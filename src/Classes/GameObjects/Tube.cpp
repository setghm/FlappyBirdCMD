#include "Tube.hpp"

Tube::Tube(double y, bool is_top_tube) : Sprite(AssetManager::getByteColor("tube")) {
	position.x = config::game::tubes_start_x;
	position.y = y;

	flipped_y = is_top_tube;

	// Avoid double scoring ignoring the top tubes.
	not_scored = !is_top_tube;

	// Configure color key.

	setColorKey(Color::red);

	setCollisionIgnoreColorKey(true);

	// Configure default physics.

	body.setVelocityX(config::game::tubes_velocity);
}

bool Tube::canScore(double bird_width) {
	// Check if the tube has passed the middle X position of the bird.
	if (not_scored) {

		if (left() < (config::player::start_x + bird_width)) {
			not_scored = false; // Already check this tube.

			return true;
		}

	}

	return false;
}
