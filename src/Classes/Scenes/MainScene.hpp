#pragma once

#include <GameEngine/GameEngine.hpp>
#include "../GameObjects/Tube.hpp"

#include <vector>

class MainScene : public Scene {
private:
	std::vector<Tube*> tubes;

	void addTubesPair(void);
public:
	MainScene();

	~MainScene();

	void update(double delta_time) override;

	void draw(void) override;
};

