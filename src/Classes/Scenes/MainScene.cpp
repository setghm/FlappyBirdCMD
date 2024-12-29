#include "MainScene.hpp"
#include "../GameObjects/Bird.hpp"

MainScene::MainScene() {
	Bird* bird = new Bird();

	addChild(bird);
}