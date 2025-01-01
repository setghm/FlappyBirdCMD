#include "Obstacles.hpp"
#include "Tube.hpp"

Obstacles::Obstacles(void) : Container() {
	// Create the tubes container.
	tubes = new Container();

	addChild(tubes);

	// Configure a timer to spawn a new pair of tubes.
	spawn_timer = new Timer();

	spawn_timer->setAction([this](void) {
		spawn();
	});

	spawn_timer->setDuration(config::game::duration_tubes_generation);

	spawn_timer->setLoop(true);

	addChild(spawn_timer);
}

void Obstacles::update(double delta_time) {
	Container::update(delta_time);
	
	// Filter tubes that have disappeared on the left side.
	auto& obstacles = tubes->getChildren();

	for (auto it = obstacles.begin(); it != obstacles.end();) {
		const auto tube = dynamic_cast<const Tube*>(*it);

		if (tube) {
			if (tube->getX() + tube->getWidth() < 0) {
				delete tube;
				it = obstacles.erase(it);

				continue;
			}
		}

		it++;
	}
}

void Obstacles::restart(void) {
	tubes->clear();

	spawn_timer->restart();
}

void Obstacles::spawn(void) {
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

	tubes->addChild(top_tube);
	tubes->addChild(bottom_tube);
}
