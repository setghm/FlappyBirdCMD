#pragma once

#include <GameEngine/GameEngine.hpp>

class Score : public GameObject {
private:
	uint32_t score;

	ColorData numbers;

	double y;
public:
	void draw(void);

	void update(double delta_time) override {}

	void input(InputEvent* event) override {}

	Score(void);

	void increment(void);

	void restart(void);
};

