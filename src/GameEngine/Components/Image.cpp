#include "Image.hpp"
#include "../Console.hpp"

Image::Image(void) {
	data.size = { 0 };
	data.colors = { 0 };
	data.color_key = Color::undefined;
}

Image::Image(ByteColorImage* image) : Image() {
	data.size.height = image->height;
	data.size.width = image->width;
	data.colors = image->data;
}

void Image::draw(void) {
	if (!visible) return;

	const double w = static_cast<double>(data.size.width);
	const double h = static_cast<double>(data.size.height);
	const double x = static_cast<int>(position.x);
	const double y = static_cast<int>(position.y);

	const Rect2d data_rect { 0, 0, w, h };

	const Rect2d screen_rect {
		flipped_x ? x + w : x,
		flipped_y ? y + h : y,
		flipped_x ? -w : w,
		flipped_y ? -h : h
	};

	Console::getInstance()->draw(data, data_rect, screen_rect);
}
