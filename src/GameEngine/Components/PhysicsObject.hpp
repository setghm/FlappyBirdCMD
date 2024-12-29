#pragma once

#include "../Types.hpp"
#include "GameObject.hpp"

class PhysicsObject : public GameObject {
protected:
	Vector2 acceleration;
	Vector2 position;
	Vector2 velocity;
public:
	PhysicsObject();

	/*
	* Updates the physics object.
	*/
	virtual void update(double delta_time) override;

	// Accessors.

	/*
	* The current object position.
	*/
	Vector2 getPosition(void) const { return position; }

	/*
	* Horizontal position of the object in cells.
	*/
	double getX(void) const { return position.x; }

	/*
	* Vertical position of the object in cells.
	*/
	double getY(void) const { return position.y; }

	/*
	* Update the object position.
	*/
	inline void setPosition(double x, double y) { position.x = x; position.y = y; }
	inline void setPosition(Vector2 position) { this->position.x = position.x; this->position.y = position.y; }

	/*
	* Update the horizontal position.
	*/
	inline void setX(double x) { position.x = x; }

	/*
	* Update the vertical position.
	*/
	inline void setY(double y) { position.y = y; }

	/*
	* Horizontal velocity of the object in cells/second.
	*/
	double getVelocityX(void) const { return velocity.x; }

	/*
	* Vertical velocity of the object in cells/second.
	*/
	double getVelocityY(void) const { return velocity.y; }

	/*
	* Update the object velocity.
	*/
	inline void setVelocity(double vx, double vy) { velocity.x = vx; velocity.y = vy; }

	/*
	* Update the horizontal velocity in cells/second.
	*/
	inline void setVelocityX(double vx) { velocity.x = vx; }

	/*
	* Update the vertical velocity in cells/second.
	*/
	inline void setVelocityY(double vy) { velocity.y = vy; }
};

