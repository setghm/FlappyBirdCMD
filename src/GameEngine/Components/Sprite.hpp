#pragma once

#include <vector>
#include <cinttypes>

#include "../Types.hpp"
#include "../Addons/bytecolor_loader.hpp"
#include "../../Configuration.hpp"
#include "PhysicsObject.hpp"

class Sprite : public PhysicsObject {
private:
	Size2d size;
	std::vector<uint8_t> data;
protected:
	Rect2d world_bounds;
public:
	/*
	* Creates a new Sprite with empty data.
	*/
	Sprite(void);

	/*
	* Creates a Sprite from a ByteColorImage object.
	*/
	Sprite(ByteColorImage* bytecolor);

	/*
	* Updates the sprite physics.
	*/
	virtual void update(double delta_time) override;

	/*
	* Draws the sprite into the console buffer.
	*/
	virtual void draw(void) override;

	/*
	* Skips the implementation for this method.
	*/
	virtual void input(InputEvent* event) override {}

	// Accessors.

	/*
	* The current size of the sprite.
	*/
	Size2d getSize(void) const { return size; }

	/*
	* Width of the sprite in cells.
	*/
	double getWidth(void) const { return size.width; }

	/*
	* Height of the sprite in cells.
	*/
	double getHeight(void) const { return size.height; }

	/*
	* The colour data of the sprite.
	*/
	const std::vector<uint8_t>& getData(void) const { return data; }

	/*
	* Sets the colour data, width and height from a ByteColorImage object.
	*/
	inline void setData(ByteColorImage* image) { data = image->data; size.width = image->width; size.height = image->height; }

	/*
	* The current limits of the sprite.
	*/
	Rect2d getWorldBounds(void) const { return world_bounds; }

	/*
	* Set the world limits for this sprite.
	*/
	inline void setWorldBounds(double x, double y, uint32_t width, uint32_t height) {
		world_bounds.x = x;
		world_bounds.y = y;
		world_bounds.width = width;
		world_bounds.height = height;
	}
	inline void setWorldBounds(double x1, double y1, double x2, double y2) {
		world_bounds.x = x1;
		world_bounds.y = y1;
		world_bounds.width = static_cast<uint32_t>(x2 - x1);
		world_bounds.height = static_cast<uint32_t>(y2 - y1);
	}
	inline void setWorldBounds(Rect2d world_bounds) { this->world_bounds = world_bounds; }

	/*
	* Set the world limits for this sprite as screen limits.
	*/
	inline void setWorldBoundsAsScreen(void) {
		world_bounds.x = 0;
		world_bounds.y = 0;
		world_bounds.width = config::screen::width;
		world_bounds.height = config::screen::height;
	}
};

