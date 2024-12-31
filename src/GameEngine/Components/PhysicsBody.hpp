#pragma once

#include "../Types.hpp"

class PhysicsBody {
private:
	Vector2 acceleration;
	Vector2 velocity;
public:
	PhysicsBody() : acceleration({ 0 }), velocity({ 0 }) {}

	/*
	* Updates a given position according to physics.
	*/
	void updatePosition(double delta_time, Vector2& position) {
		velocity.x += acceleration.x * delta_time;
		velocity.y += acceleration.y * delta_time;

		position.x += velocity.x * delta_time;
		position.y += velocity.y * delta_time;
	}

	// Accessors.

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

	/*
	* Horizontal acceleration of the object in cells/second ^ 2.
	*/
	double getAccelerationX(void) const { return velocity.x; }

	/*
	* Vertical acceleration of the object in cells/second ^ 2.
	*/
	double getAccelerationY(void) const { return velocity.y; }

	/*
	* Update the object acceleration.
	*/
	inline void setAcceleration(double ax, double ay) { acceleration.x = ax; acceleration.y = ay; }

	/*
	* Update the horizontal acceleration in cells/second ^ 2.
	*/
	inline void setAccelerationX(double ax) { acceleration.x = ax; }

	/*
	* Update the vertical acceleration in cells/second ^ 2.
	*/
	inline void setAccelerationY(double ay) { acceleration.y = ay; }
};

