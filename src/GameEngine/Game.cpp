#include "Game.hpp"
#include "Console.hpp"
#include <chrono>
#include <exception>

Game::Game(void) {
	running = true;
	active_scene_name = "";
}

Game::~Game(void) {
	for (auto& pair : scenes) {
		delete pair.second;
	}

	scenes.clear();
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

		// Retrieve the active scene.
		Scene* scene = scenes[active_scene_name];

		// Check for input events and process.
		InputEvent* event = console->checkInput();

		if (event != nullptr) {
			scene->input(event);
			delete event;
		}

		// Update and draw the active scene.
		scene->update(delta_time.count());
		scene->draw();

		// Render the console buffer.
		console->presentBuffer();
	}

	Console::destroyInstance();

	return 0;
}

void Game::addScene(std::string name, Scene* scene) {
	const uint32_t id = static_cast<uint32_t>(scenes.size() - 1);
	
	scene->setChangeSceneCallback([this](std::string name, void* args) {
		setActiveScene(name, args);
	});
	
	scenes[name] = scene;
}

void Game::setActiveScene(std::string name, void* args) {
	auto scene = scenes.find(name);

	if (scene == scenes.end()) {
		throw std::exception("Scene not found");
	}

	active_scene_name = name;

	scenes[name]->sceneJustCalled(args);
}