#pragma once

#include "../InputEvents.hpp"

class GameObject {
public:
	/*
	* Draws the object on the screen.
	*/
	virtual void draw() = 0;
	
	/*
	* Called each frame, updates the object properties.
	*/
	virtual void update(double delta_time) = 0;

	/*
	* Process an incoming input event.
	*/
	virtual void input(InputEvent* event) = 0;
};

