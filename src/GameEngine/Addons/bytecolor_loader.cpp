#include "bytecolor_loader.hpp"

ByteColorImage* ByteColorImage::fromFile(std::string filename) {
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + filename);
	}

	ByteColorImage* image = new ByteColorImage();
	
	try {
		// Read image dimensions.
		file.read(reinterpret_cast<char*>(&image->width), sizeof(image->width));
		file.read(reinterpret_cast<char*>(&image->height), sizeof(image->height));

		if (file.fail()) {
			throw std::runtime_error("Failed to read image dimensions.");
		}

		// Calculate the array size.
		size_t data_size = image->width * image->height;
		image->data.reserve(data_size);

		image->data.insert(
			image->data.begin(),
			std::istream_iterator<unsigned char>(file),
			std::istream_iterator<unsigned char>()
		);
		
		file.close();

		return image;
	}
	catch (const std::exception& e) {
		delete image;
		file.close();
		throw;
	}
}
