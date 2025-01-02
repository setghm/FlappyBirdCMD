#include "MainScene.hpp"

#include <iostream>

MainScene::MainScene() : Scene() {
	// Create the background.
	background = new Background();

	addChild(background); // Drawn first

	// Create the bird object.
	bird = new Bird();

	addChild(bird);

	// Create the obstacles object.

	obstacles = new Obstacles();

	addChild(obstacles);

	// Create the score object.
	score = new Score();

	addChild(score);

	// Create game over labels.
	game_over_label = new Image(AssetManager::getByteColor("game over"));
	start_label = new Image(AssetManager::getByteColor("press start"));

	game_over_label->setPosition(
		(config::screen::width - game_over_label->getWidth()) / 2,
		config::game::title_y
	);
	game_over_label->setColorKey(Color::red);

	start_label->setPosition(
		(config::screen::width - start_label->getWidth()) / 2,
		config::game::start_label_y
	);
	start_label->setColorKey(Color::red);

	addChild(game_over_label);
	addChild(start_label);

	// Create a blink timer for the "press to start" image text.

	blink = new Timer();

	blink->setDuration(config::game::duration_blink);
	blink->setLoop(true);

	blink->setAction([this](void) {
		start_label->setVisible(!start_label->isVisible());
	});

	addChild(blink);

	// By default hide the game over items.

	blink->pause();
	game_over_label->setVisible(false);
	start_label->setVisible(false);

	game_over = false;
}

void MainScene::restart(void) {
	bird->restart();
	obstacles->restart();
	score->restart();

	background->start();

	bird->setInteractive(true);
	bird->setFreezed(false);
	obstacles->setFreezed(false);

	game_over_label->setVisible(false);
	start_label->setVisible(false);
	blink->pause();
	blink->restart();

	game_over = false;
}

void MainScene::update(double delta_time) {
	Scene::update(delta_time);

	// Don't check for collisions and score if the game is over.
	if (game_over) return;

	obstacles->getTubes()->forEach([this](GameObject* obstacle, int index) {
		const auto tube = dynamic_cast<Tube*>(obstacle);

		if (!tube) return;

		// Check if player has scored.
		if (tube->canScore(bird->getWidth())) {
			score->increment();
		}

		// Check collisions with bird.
		bool bird_colliding = bird->checkCollision(tube);

 		if (bird_colliding) {
			game_over = true;

			bird->setInteractive(false);
			bird->setFreezed(true);
			obstacles->setFreezed(true);
			background->stop();

			game_over_label->setVisible(true);
			start_label->setVisible(true);
			blink->resume();
		}
	});
}

void MainScene::input(InputEvent* event) {
	Scene::input(event);

	if (game_over && event->isKeyboardEvent()) {
		const KeyboardEvent* kbe = event->toKeyboardEvent();

		if (kbe->anyKeyPressed()) {
			restart();
		}
	}
}
