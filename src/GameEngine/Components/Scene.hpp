#pragma once

#include <vector>
#include "GameObject.hpp"

class Scene : protected GameObject {
private:
	std::vector<GameObject*> children;
public:
	/*
	* Updates the scene's children.
	*/
	virtual void update(double delta_time) override;

	/*
	* Draws the scene's children.
	*/
	virtual void draw(void) override;

	/*
	* Process the given input event for all the objects.
	*/
	virtual void input(InputEvent* event) override;

	/*
	* Adds a game object pointer and its ownership to this scene,
	* so you don't need to remove it manually.
	*/
	void addChild(GameObject* child);

	/*
	* Removes a game object and its ownership, so you need to remove it
	* manually.
	*/
	GameObject* removeChild(GameObject* child);

	/*
	* When the scene is deleted, all its children are deleted too.
	*/
	~Scene();
};

