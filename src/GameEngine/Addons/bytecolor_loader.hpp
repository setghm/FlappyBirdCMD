/*
	Bytecolor loader for C++
	setghm (c) 2024

	Include these 2 files in your project in order to load your generated .bytecolor
	images into your console application.
*/
#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

class ByteColorImage {
public:
	/*
		Width of the image in characters.
	*/
	unsigned long int width;

	/*
		Height of the image in characters.
	*/
	unsigned long int height;

	/*
		Colors of the image (one element per color).
	*/
	std::vector<unsigned char> data;

	/*
		Loads a .bytecolor file given its file path and returns a new pointer to a ByteColorImage object or throws a runtime_exception.
	*/
	static ByteColorImage* fromFile(std::string filename);
};
