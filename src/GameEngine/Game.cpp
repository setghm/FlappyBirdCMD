#include "Game.hpp"
#include "Console.hpp"
#include <chrono>

Game::Game(void) {
	running = true;
	active_scene = 0;
}

Game::~Game(void) {
	for (Scene* scene : scenes) {
		delete scene;
	}

	(void)scenes.empty();
}

int Game::play(void) {
	Console* console = Console::getInstance();

	std::chrono::steady_clock::time_point current_time, last_time;
	std::chrono::duration<double> delta_time;

	last_time = std::chrono::high_resolution_clock::now();

	while (running) {
		// Calculate the delta time.
		current_time = std::chrono::high_resolution_clock::now();
		delta_time = current_time - last_time;
		last_time = current_time;

		// Clear the console buffer.
		console->clear();

		// Get the active scene.
		Scene* scene = scenes[active_scene];

		// Check for input events and process.
		InputEvent* event = console->checkInput();

		if (event != nullptr) {
			scene->input(event);
			delete event;
		}

		// Draw and update the active scene.
		scene->update(delta_time.count());
		scene->draw();

		// Render the console buffer.
		console->presentBuffer();
	}

	Console::destroyInstance();

	return 0;
}

uint32_t Game::addScene(Scene* scene) {
	scenes.push_back(scene);
	return static_cast<uint32_t>(scenes.size() - 1);
}

void Game::setActiveScene(uint32_t scene_id) {
	if (scene_id < scenes.size()) {
		active_scene = scene_id;
	}
}