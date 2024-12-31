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
public:
	MainScene();

	~MainScene();

	void update(double delta_time) override;

	void draw(void) override;
};

