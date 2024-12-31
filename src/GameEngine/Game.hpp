#pragma once

#include <cinttypes>
#include <map>
#include <string>
#include "Components/Scene.hpp"

class Game {
private:
	std::map<std::string, Scene*> scenes;
	Scene* active_scene;
	bool running;
public:
	Game(void);

	/*
	* Releases all the added scenes and its children, any scene or object
	* not included here must be released manually.
	*/
	~Game(void);

	/*
	* Start the main loop for the game object.
	*/
	int play(void);

	/*
	* Adds the desired scene to the game scenes and returns its ID.
	*/
	void addScene(std::string name, Scene* scene);

	/*
	* Set the active scene from its index.
	*/
	void setActiveScene(std::string name);
};

