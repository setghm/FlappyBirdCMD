#include "AssetManager.hpp"

#include <iostream>

std::map<std::string, ByteColorImage*> AssetManager::bytecolors;

void AssetManager::cleanup(void) {
	// Release all the prealoaded bytecolor images.
	for (const auto& pair : bytecolors) {
		delete pair.second;
	}

	(void)bytecolors.empty();
}

void AssetManager::preloadByteColor(std::string name, std::string path) {
	ByteColorImage* image = ByteColorImage::fromFile(path);
	AssetManager::bytecolors[name] = image;
}

ByteColorImage* AssetManager::getByteColor(std::string name) {
	return AssetManager::bytecolors[name];
}
