#pragma once

#include <GameEngine/GameEngine.hpp>

class Bird : public Sprite {
private:
	ByteColorImage* frame_falling;
	ByteColorImage* frame_flying;
	bool falling;
public:
	Bird();

	void update(double delta_time) override;
	void input(InputEvent* event) override;
};

