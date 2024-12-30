#include "Tube.hpp"

Tube::Tube(double x, double y) : Sprite(AssetManager::getByteColor("tube")) {
	position.x = x;
	position.y = y;
}
