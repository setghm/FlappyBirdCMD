#include "StartScene.hpp"

StartScene::StartScene(void) : Scene() {
	start = new Image(AssetManager::getByteColor("press start"));
	title = new Image(AssetManager::getByteColor("title"));
	background = new Background();

	addChild(background);
	addChild(start);
	addChild(title);

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
			
		}

	}
}
