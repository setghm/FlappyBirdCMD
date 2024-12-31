#include "Timer.hpp"

Timer::Timer() : GameObject() {
	elapsed_time = 0;
	duration = 0;
	action = [](void) {};
	loop = false;
	executed_once = false;
}

void Timer::update(double delta_time) {
	elapsed_time += delta_time;

	if ((elapsed_time >= duration) && (loop || !executed_once)) {
		action();

		if (loop) {
			elapsed_time = 0;
		}
		else {
			executed_once = true;
		}
	}
}
