#pragma once

#include <GameEngine/GameEngine.hpp>

#include "../GameObjects/Background.hpp"

class StartScene : public Scene {
private:
	Image* start;
	Image* title;
	Background* background;
public:
	StartScene(void);

	void input(InputEvent* event) override;

	void draw(void) override;
};
