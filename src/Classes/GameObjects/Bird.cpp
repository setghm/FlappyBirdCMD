#include "Bird.hpp"

Bird::Bird() {
	frame_falling = AssetManager::getByteColor("bird falling");
	frame_flying = AssetManager::getByteColor("bird flying");

	position.x = config::player::start_x;
	position.y = config::player::start_y;
	acceleration.y = config::game::gravity;

	setWorldBoundsAsScreen();

	setData(frame_falling);

	falling = true;
}

void Bird::update(double delta_time) {
	Sprite::update(delta_time);

	if (velocity.y > 0 && falling) {
		falling = false;
		setData(frame_falling);
	}
	else if (velocity.y < 0 && !falling) {
		falling = true;
		setData(frame_flying);
	}
}

void Bird::input(InputEvent* event) {
	if (event->type == InputEventType::keyboard) {
		KeyboardEvent* ke = static_cast<KeyboardEvent*>(event);

		if (ke->keycode == 32 && !ke->is_pressed) {
			setVelocityY(config::player::jump_velocity);
		}
	}
}
