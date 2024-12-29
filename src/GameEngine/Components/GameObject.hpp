#pragma once

#include "../InputEvents.hpp"

class GameObject {
public:
	virtual void update(double delta_time) = 0;
	virtual void draw() = 0;
	virtual void input(InputEvent* event) = 0;
};

