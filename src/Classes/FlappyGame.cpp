#include "FlappyGame.hpp"
#include "Scenes/MainScene.hpp"

FlappyGame::FlappyGame() {
	// Preload all the assets.
	AssetManager::preloadByteColor("bird flying", "assets/bird-pos1.bytecolor");
	AssetManager::preloadByteColor("bird falling", "assets/bird-pos2.bytecolor");
	AssetManager::preloadByteColor("tube", "assets/tube.bytecolor");

	// Create the scenes.
	MainScene *mainScene = new MainScene();

	int mainSceneId = addScene(mainScene);

	// Activate the start scene.
	setActiveScene(mainSceneId);
}