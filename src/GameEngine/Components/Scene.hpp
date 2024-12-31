#pragma once

#include <string>
#include <functional>
#include <vector>
#include "GameObject.hpp"

typedef std::function<void(std::string name)> ChangeSceneCallback;

class Scene : protected GameObject {
private:
	std::vector<GameObject*> children;
protected:
	ChangeSceneCallback changeScene;
public:
	Scene(void) : changeScene([](std::string name) {}) {}

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

	// Accessors.

	/*
	* Set the change scene callback, don't call this explicitly.
	*/
	inline void setChangeScene(ChangeSceneCallback callback) { changeScene = callback; }
};

