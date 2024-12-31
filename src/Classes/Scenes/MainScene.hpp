#pragma once

#include <GameEngine/GameEngine.hpp>
#include "../GameObjects/Tube.hpp"
#include "../GameObjects/Bird.hpp"
#include "../GameObjects/Background.hpp"
#include "../GameObjects/Score.hpp"

#include <vector>

class MainScene : public Scene {
private:
	Background* background;

	Bird* bird;

	std::vector<Tube*> tubes;

	Score* score;

	void addTubesPair(void);

	bool game_over;

	Image* game_over_label;
	Image* start_label;
	Timer* blink;
public:
	VoidCallback restart;

	MainScene();

	~MainScene();

	void update(double delta_time) override;

	void draw(void) override;

	void input(InputEvent* event) override;
};

