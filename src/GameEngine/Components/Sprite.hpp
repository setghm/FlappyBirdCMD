#pragma once

#include <vector>
#include <cinttypes>

#include "../Types.hpp"
#include "../Addons/bytecolor_loader.hpp"
#include "../../Configuration.hpp"
#include "PhysicsBody.hpp"
#include "Image.hpp"

class Sprite : public Image {
protected:
	Rect2d world_bounds;
	PhysicsBody body;
	bool collision_ignore_color_key;
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
	* Checks if the sprite is collinding with another sprite.
	*/
	bool checkCollision(Sprite* other);

	// Accessors.

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

	/*
	* The current physics body.
	*/
	const PhysicsBody& getBody() const { return body; }

	/*
	* Change the values of the physics body.
	*/
	inline void setBody(PhysicsBody& body) { this->body = body; }

	/*
	* Check if the color key of the image color data (if set) is
	* currently ignored when calculating collisions.
	*/
	bool getCollisionIgnoreColorKey(void) const { return collision_ignore_color_key; }

	/*
	* Marks the color key of the image color data (if set) to be ignored
	* when calculating collisions.
	*/
	inline void setCollisionIgnoreColorKey(bool ignore) { collision_ignore_color_key = ignore; }

};

