#pragma once

#include <GameEngine/GameEngine.hpp>

class Tube : public Sprite {
private:
	bool not_scored;
public:
	Tube(double y, bool is_top_tube = false);

	/*
	* Check if the tube has passed the required position to increment the
	* player score.
	*/
	bool canScore(double bird_width);
};

