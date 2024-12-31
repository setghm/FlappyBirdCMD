#pragma once

#include <GameEngine/GameEngine.hpp>

class Background : public GameObject {
private:
	Rect2d tile_draw_rect;

	ColorData tile;
	Color fill_color;
	double tiles_start_y;
	double tiles_start_x;
	double tile_velocity_x;
public:
	Background(void);

	void draw(void) override;

	void update(double delta_time) override;

	void input(InputEvent* event) override {}

	/*
	* Stops the background movement.
	*/
	void stop(void);

	/*
	* Starts or resumes the background movement.
	*/
	void start(void);

	/*
	* The last position along X axis.
	*/
	double getX(void) const { return tiles_start_x; }
};

