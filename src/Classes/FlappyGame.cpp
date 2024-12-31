#include "FlappyGame.hpp"
#include "Scenes/MainScene.hpp"
#include "Scenes/StartScene.hpp"

FlappyGame::FlappyGame() {
	// Preload all the assets.
	AssetManager::preloadByteColor("bird flying", "assets/bird-pos1.bytecolor");
	AssetManager::preloadByteColor("bird falling", "assets/bird-pos2.bytecolor");
	AssetManager::preloadByteColor("tube", "assets/tube.bytecolor");
	AssetManager::preloadByteColor("title", "assets/title.bytecolor");
	AssetManager::preloadByteColor("game over", "assets/game_over.bytecolor");
	AssetManager::preloadByteColor("tile", "assets/background_tile.bytecolor");
	AssetManager::preloadByteColor("numbers", "assets/numbers.bytecolor");
	AssetManager::preloadByteColor("press start", "assets/press_to_start.bytecolor");

	// Create the scenes.
	MainScene *mainScene = new MainScene();
	StartScene *startScene = new StartScene();

	addScene("main", mainScene);
	addScene("start", startScene);

	// Activate the start scene.
	setActiveScene("start");
}