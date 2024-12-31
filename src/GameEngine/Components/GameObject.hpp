#pragma once

#include "../InputEvents.hpp"

class GameObject {
protected:
	bool freezed;
	bool visible;
	bool interactive;
public:
	/*
	* By default a game object is visible, not freezed and interactive.
	*/
	GameObject(void) : freezed(false), visible(true), interactive(true) {}

	/*
	* Draws the object on the screen.
	*/
	virtual void draw(void) = 0;
	
	/*
	* Called each frame, updates the object properties.
	*/
	virtual void update(double delta_time) = 0;

	/*
	* Process an incoming input event.
	*/
	virtual void input(InputEvent* event) = 0;

	// Accessors.
	
	/*
	* Should the current object be updated.
	*/
	bool isFreezed(void) const { return freezed; }

	/*
	* Freeze or resume this object.
	*/
	inline void setFreezed(bool freezed) { this->freezed = freezed; }

	/*
	* Should the current object be drawed.
	*/
	bool isVisible(void) const { return visible; }

	/*
	* Show or hide this object.
	*/
	inline void setVisible(bool visible) { this->visible = visible; }

	/*
	* Should the current object receive input events.
	*/
	bool isInteractive(void) const { return interactive; }

	/*
	* Set interactive or not this object.
	*/
	inline void setInteractive(bool interactive) { this->interactive = interactive; }
};

