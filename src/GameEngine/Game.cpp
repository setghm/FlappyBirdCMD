#include "Game.hpp"
#include "Console.hpp"
#include <chrono>
#include <exception>

Game::Game(void) {
	running = true;
	active_scene = nullptr;
}

Game::~Game(void) {
	for (auto& pair : scenes) {
		delete pair.second;
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

		// Check for input events and process.
		InputEvent* event = console->checkInput();

		if (event != nullptr) {
			active_scene->input(event);
			delete event;
		}

		// Draw and update the active scene.
		active_scene->update(delta_time.count());
		active_scene->draw();

		// Render the console buffer.
		console->presentBuffer();
	}

	Console::destroyInstance();

	return 0;
}

void Game::addScene(std::string name, Scene* scene) {
	const uint32_t id = static_cast<uint32_t>(scenes.size() - 1);
	
	scene->setChangeScene([this](std::string name) {
		setActiveScene(name);
	});
	
	scenes[name] = scene;
}

void Game::setActiveScene(std::string name) {
	auto scene = scenes.find(name);

	if (scene == scenes.end()) {
		throw std::exception("Scene not found");
	}

	active_scene = scenes[name];
}