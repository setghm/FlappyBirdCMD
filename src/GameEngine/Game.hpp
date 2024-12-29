#pragma once

#include <cinttypes>
#include <vector>
#include "Components/Scene.hpp"

class Game {
private:
	std::vector<Scene*> scenes;
	uint32_t active_scene;
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
	uint32_t addScene(Scene* scene);

	/*
	* Set the active scene from its index.
	*/
	void setActiveScene(uint32_t scene_id);
};

