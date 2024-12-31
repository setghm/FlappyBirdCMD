#include "Tube.hpp"

Tube::Tube(double y, bool flip_y) : Sprite(AssetManager::getByteColor("tube")) {
	position.x = config::game::tubes_start_x;
	position.y = y;

	flipped_y = flip_y;

	// Configure color key.

	setColorKey(Color::red);

	setCollisionIgnoreColorKey(true);

	// Configure default physics.

	body.setVelocityX(config::game::tubes_velocity);
}
