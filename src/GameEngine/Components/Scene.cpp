#include "Scene.hpp"

void Scene::addChild(GameObject* child) {
	children.push_back(child);
}

GameObject* Scene::removeChild(GameObject* child) {
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
	return child;
}

void Scene::update(double delta_time) {
	for(GameObject* child : children) {
		child->update(delta_time);
	}
}

void Scene::draw(void) {
	for (GameObject* child : children) {
		child->draw();
	}
}

void Scene::input(InputEvent* event) {
	for (GameObject* child : children) {
		child->input(event);
	}
}

Scene::~Scene() {
	for (GameObject* child : children) {
		delete child;
	}

	(void)children.empty();
}