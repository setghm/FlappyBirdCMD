#include "Container.hpp"

Container::~Container() {
	clear();
}

void Container::draw(void) {
	for(GameObject* child : children) {
		if (child->isVisible()) {
			child->draw();
		}
	}
}

void Container::update(double delta_time) {
	for (GameObject* child : children) {
		if (!child->isFreezed()) {
			child->update(delta_time);
		}
	}
}

void Container::input(InputEvent* event) {
	for (GameObject* child : children) {
		if (child->isInteractive()) {
			child->input(event);
		}
	}
}

void Container::forEach(ContainerForEachCallback callback) {
	int index = 0;

	for (GameObject* child : children) {
		callback(child, index++);
	}
}

std::vector<GameObject*> Container::filter(ContainerFilterCallback callback) {
	std::vector<GameObject*> filtered{};

	for (GameObject* child : children) {
		if (callback(child)) {
			filtered.push_back(child);
		}
	}

	return filtered;
}

void Container::addChild(GameObject* child) {
	children.push_back(child);
}

GameObject* Container::removeChild(GameObject* child) {
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
	return child;
}

void Container::clear(void) {
	for (GameObject* child : children) {
		delete child;
	}

	children.clear();
}
