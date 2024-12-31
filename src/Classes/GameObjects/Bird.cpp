#include "Bird.hpp"

Bird::Bird() {
	// Load bird frames.

	frame_falling = AssetManager::getByteColor("bird falling");
	frame_flying = AssetManager::getByteColor("bird flying");

	// Configure the bird physics.

	position.x = config::player::start_x;
	position.y = config::player::start_y;

	body.setAccelerationY(config::game::gravity);

	setWorldBoundsAsScreen();

	// Configure color key.

	setColorKey(Color::red);

	setCollisionIgnoreColorKey(true);

	// Configure default properties.

	setData(frame_falling);

	falling = true;
}

void Bird::update(double delta_time) {
	Sprite::update(delta_time);

	const double vy = body.getVelocityY();

	if (vy > 0 && falling) {
		falling = false;
		setData(frame_falling);
	}
	else if (vy < 0 && !falling) {
		falling = true;
		setData(frame_flying);
	}
}

void Bird::input(InputEvent* event) {
	if (event->type == InputEventType::keyboard) {
		KeyboardEvent* ke = static_cast<KeyboardEvent*>(event);

		if (ke->keycode == 32 && !ke->is_pressed) {
			body.setVelocityY(config::player::jump_velocity);
		}
	}
}
