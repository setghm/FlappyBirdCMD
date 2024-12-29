#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject() {
	velocity = { 0 };
	position = { 0 };
	acceleration = { 0 };
}

void PhysicsObject::update(double delta_time) {
	velocity.x += acceleration.x * delta_time;
	velocity.y += acceleration.y * delta_time;

	position.x += velocity.x * delta_time;
	position.y += velocity.y * delta_time;
}
