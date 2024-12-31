#pragma once

#include <GameEngine/GameEngine.hpp>

class Obstacles : public Container {
private:
	void spawn(void);

	Container* tubes;
	Timer* spawn_timer;
public:
	Obstacles(void);

	void update(double delta_time) override;

	void restart(void);

	// Accessors.
	Container* getTubes(void) { return tubes; }
};

