#include "FlappyGame.hpp"
#include "Scenes/MainScene.hpp"

FlappyGame::FlappyGame() {
	// Preload all the assets.
	AssetManager::preloadByteColor("bird flying", "assets/bird-pos1.bytecolor");
	AssetManager::preloadByteColor("bird falling", "assets/bird-pos2.bytecolor");
	AssetManager::preloadByteColor("tube", "assets/tube.bytecolor");
	AssetManager::preloadByteColor("title", "assets/title.bytecolor");
	AssetManager::preloadByteColor("game over", "assets/game_over.bytecolor");
	AssetManager::preloadByteColor("title", "assets/background_tile.bytecolor");
	AssetManager::preloadByteColor("numbers", "assets/numbers.bytecolor");
	AssetManager::preloadByteColor("press start", "assets/press_to_start.bytecolor");

	// Create the scenes.
	MainScene *mainScene = new MainScene();

	int mainSceneId = addScene(mainScene);

	// Activate the start scene.
	setActiveScene(mainSceneId);
}