#pragma once

#include <GameEngine/GameEngine.hpp>

class Bird : public Sprite {
private:
	ByteColorImage* frame_falling;
	ByteColorImage* frame_flying;
	bool falling;
	bool death;
public:
	Bird();

	void update(double delta_time) override;
	void input(InputEvent* event) override;

	void setDeath(bool death) { this->death = death; }
};

