#include "StartScene.hpp"

StartScene::StartScene(void) : Scene() {
	start = new Image(AssetManager::getByteColor("press start"));
	title = new Image(AssetManager::getByteColor("title"));
	background = new Background();

	addChild(background);
	addChild(start);
	addChild(title);

	// Configure objects.
	title->setPosition(
		(config::screen::width - title->getWidth()) / 2,
		config::game::title_y
	);

	title->setColorKey(Color::red);

	start->setPosition(
		(config::screen::width - start->getWidth()) / 2,
		config::game::start_label_y
	);

	start->setColorKey(Color::red);

	// Add timer to blink the start label.
	Timer* blink = new Timer();

	blink->setDuration(config::game::duration_blink);
	
	blink->setLoop(true);

	blink->setAction([this](void) {
		start->setVisible(!start->isVisible());
	});

	addChild(blink);
}

void StartScene::input(InputEvent* event) {
	if (event->type == InputEventType::keyboard) {

		const KeyboardEvent* ev = static_cast<KeyboardEvent*>(event);

		if (ev->is_pressed) {
			changeScene("main");
		}
	}
}

void StartScene::draw(void) {
	Scene::draw();

	// Draw the author name.
	Console::getInstance()->drawString("setghm 2025", 1, config::screen::height - 2);
}
