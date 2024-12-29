#pragma once

#include <string>
#include <map>

#include "Addons/bytecolor_loader.hpp"

class AssetManager {
private:
	static std::map<std::string, ByteColorImage*> bytecolors;
public:
	/*
	* Releases all the preloaded assets.
	*/
	static void cleanup(void);

	/*
	* Preloads a bytecolor image file, this method can raises an exception if
	* an error occurs.
	*/
	static void preloadByteColor(std::string name, std::string path);

	/*
	* Retrieves a prealoaded bytecolor image, if the image was not loaded a
	* nullptr will be returned.
	*/
	static ByteColorImage* getByteColor(std::string name);
};

