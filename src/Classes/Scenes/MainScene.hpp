#pragma once

#include <GameEngine/GameEngine.hpp>
#include "../GameObjects/Tube.hpp"
#include "../GameObjects/Obstacles.hpp"
#include "../GameObjects/Bird.hpp"
#include "../GameObjects/Background.hpp"
#include "../GameObjects/Score.hpp"

#include <vector>

class MainScene : public Scene {
private:
	Background* background;
	Bird* bird;
	Obstacles* obstacles;
	Score* score;

	bool game_over;

	Image* game_over_label;
	Image* start_label;
	Timer* blink;
public:
	MainScene();

	void restart(void);

	void update(double delta_time) override;

	void input(InputEvent* event) override;
};

