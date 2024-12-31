#include "MainScene.hpp"

#include <iostream>

MainScene::MainScene() : Scene() {
	// Create the background.
	background = new Background();

	addChild(background); // Drawn first

	// Create the bird object.
	bird = new Bird();

	addChild(bird);

	// Configure a timer to spawn a new pair of tubes.
	Timer* tubes_timer = new Timer();

	tubes_timer->setAction([this](void) {
		addTubesPair();
	});

	tubes_timer->setDuration(config::game::duration_tubes_generation);

	tubes_timer->setLoop(true);

	addChild(tubes_timer);

	// Generate the first pair of tubes.
	addTubesPair();

	// Create the score object.
	score = new Score();

	// By default the restart callback does nothing.
	restart = [](void) {};

	// Create game over labels.
	game_over_label = new Image(AssetManager::getByteColor("game over"));
	start_label = new Image(AssetManager::getByteColor("press start"));

	game_over_label->setPosition(
		(config::screen::width - game_over_label->getWidth()) / 2,
		config::screen::height * 0.2
	);
	game_over_label->setColorKey(Color::black);

	start_label->setPosition(
		(config::screen::width - start_label->getWidth()) / 2,
		config::screen::height * 0.75
	);
	start_label->setColorKey(Color::black);

	blink = new Timer();

	blink->setDuration(config::game::duration_blink);
	blink->setLoop(true);

	blink->setAction([this](void) {
		start_label->setVisible(!start_label->isVisible());
	});
}

MainScene::~MainScene() {
	Scene::~Scene();

	delete score;
	delete game_over_label;
	delete start_label;
	delete blink;

	for (Tube* tube : tubes) {
		delete tube;
	}

	(void)tubes.empty();
}

void MainScene::addTubesPair(void) {
	// Select a random spacing between tubes.
	const double spacing = utils::rand(config::game::tubes_min_space, config::game::tubes_max_space);

	// Select a random Y middle point.
	const double middle_y = utils::rand(config::game::tubes_min_middle_y, config::game::tubes_max_middle_y);

	// Get the tube image height.
	const int tube_height = AssetManager::getByteColor("tube")->height;

	// Calculate the Y position for tubes.
	const double top_y = (middle_y - spacing / 2) - tube_height;
	const double bottom_y = middle_y + spacing / 2;

	Tube* top_tube = new Tube(top_y, true);
	Tube* bottom_tube = new Tube(bottom_y);

	tubes.push_back(top_tube);
	tubes.push_back(bottom_tube);
}

void MainScene::update(double delta_time) {
	// If game is over don't update tubes only the blink timer.
	if (game_over) {
		blink->update(delta_time);
		return;
	}

	Scene::update(delta_time);

	for (auto it = tubes.begin(); it != tubes.end(); ) {
		Tube* tube = *it;
		tube->update(delta_time);

		// Remove tubes that have disappeared on the left side.
		if (tube->getX() + tube->getWidth() < 0) {
			delete tube;
			it = tubes.erase(it);
			
			continue;
		}

		// Check if player has scored.
		if (tube->canScore(bird->getWidth())) {
			score->increment();
		}
		
		// Check collisions with bird.
		bool bird_colliding = bird->checkCollision(tube);

		if (bird_colliding) {
			game_over = true;
			bird->setDeath(true);
		}

		it++;
	}
}

void MainScene::draw(void) {
	Scene::draw();

	for (Tube* tube : tubes) {
		tube->draw();
	}

	score->draw(); // Draw at the top of everything (while playing).

	// Draw at the top of everything (while in game over state).
	if (game_over) {
		game_over_label->draw();
		start_label->draw();
	}
}

void MainScene::input(InputEvent* event) {
	Scene::input(event);

	if (game_over && event->type == InputEventType::keyboard) {

		const KeyboardEvent* ev = static_cast<KeyboardEvent*>(event);

		if (ev->is_pressed) {
			restart();
		}
	}
}
