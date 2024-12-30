#include "MainScene.hpp"
#include "../GameObjects/Bird.hpp"

MainScene::MainScene() {
	// Create the bird object.
	Bird* bird = new Bird();

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
}

MainScene::~MainScene() {
	Scene::~Scene();

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

	Tube* top_tube = new Tube(config::game::tubes_start_x, top_y);
	Tube* bottom_tube = new Tube(config::game::tubes_start_x, bottom_y);

	top_tube->setVelocityX(config::game::tubes_velocity);
	bottom_tube->setVelocityX(config::game::tubes_velocity);

	tubes.push_back(top_tube);
	tubes.push_back(bottom_tube);
}

void MainScene::update(double delta_time) {
	Scene::update(delta_time);

	for (auto it = tubes.begin(); it != tubes.end(); ) {
		Tube* tube = *it;
		tube->update(delta_time);

		// Remove tubes that have disappeared on the left side.
		if (tube->getX() + tube->getWidth() < 0) {
			delete tube;
			it = tubes.erase(it);
		}
		else {
			it++;
		}
	}
}

void MainScene::draw(void) {
	Scene::draw();

	for (Tube* tube : tubes) {
		tube->draw();
	}
}

