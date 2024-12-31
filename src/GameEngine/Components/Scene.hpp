#pragma once

#include <string>
#include <functional>
#include <vector>
#include "Container.hpp"

typedef std::function<void(std::string name, void* args)> ChangeSceneCallback;

class Scene : protected Container {
private:
	ChangeSceneCallback changeSceneCallback;
protected:
	/*
	* Change the active scene to another one given its name.
	* 
	* If the scene doesn't exists an std::exception will be thrown.
	* 
	* Optionally the new scene may receive arguments of any type using a
	* void pointer.
	* 
	* If the arguments are a block in memory that requires freeing, this
	* can be done after calling this method since the sceneJustCalled method
	* of the other scene will be executed instantly when calling this method.
	*/
	void changeScene(std::string name, void* args = nullptr) const { changeSceneCallback(name, args); }

public:
	Scene(void) : Container(), changeSceneCallback([](std::string name, void* args) {}) {}

	/*
	* Draws all the scene's children on the screen.
	*/
	virtual void draw(void) override { Container::draw(); }

	/*
	* Updates all the scene's children.
	*/
	virtual void update(double delta_time) override { Container::update(delta_time); }

	/*
	* Process an input event on each of the scene's children.
	*/
	virtual void input(InputEvent* event) override { Container::input(event); }

	/*
	* Use this method to setup properties when the scene is just called.
	*/
	virtual void sceneJustCalled(void* args) {}

	// Accessors.

	/*
	* Set the change scene callback, don't call this explicitly.
	*/
	inline void setChangeSceneCallback(ChangeSceneCallback callback) { changeSceneCallback = callback; }
};

