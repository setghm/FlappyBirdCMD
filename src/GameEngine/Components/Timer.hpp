#pragma once

#include "GameObject.hpp"
#include <functional>

class Timer : public GameObject {
private:
	bool loop;
	double duration; // In seconds.
	std::function<void(void)> action;

	double elapsed_time; // In seconds.
	bool executed_once;
public:
	Timer();

	/*
	* Updates the timer each frame.
	*/
	virtual void update(double delta_time) override;

	/*
	* Skip the implementation for draw.
	*/
	virtual void draw(void) override {}

	/*
	* Skip the implementation for input.
	*/
	virtual void input(InputEvent* event) override {}

	/*
	* The sleep duration in seconds.
	*/
	double getDuration(void) const { return duration; }

	/*
	* Set the sleep duration in seconds.
	*/
	inline void setDuration(double value) { duration = value; }

	/*
	* The action to be executed when the wait ends.
	*/
	std::function<void(void)> getAction(void) { return action; }

	/*
	* Sets the new action to be executed when the wait ends.
	*/
	inline void setAction(std::function<void(void)> action) { this->action = action; }

	/*
	* The timer should be executed once or forever.
	*/
	bool isLooping(void) const { return loop; }

	/*
	* Set the loop mode.
	*/
	inline void setLoop(double loop) { this->loop = loop; }
};

