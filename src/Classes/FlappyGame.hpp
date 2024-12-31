#pragma once

#include <GameEngine/GameEngine.hpp>

class FlappyGame : public Game {
private:
	void onInput(InputEvent* event) override;
public:
	FlappyGame();
};

