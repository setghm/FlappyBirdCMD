#include "Score.hpp"

#include <cmath>

Score::Score(void) : GameObject() {
	score = 0;

	ByteColorImage* image = AssetManager::getByteColor("numbers");

	numbers.colors = image->data;
	numbers.size.width = image->width;
	numbers.size.height = image->height;
	numbers.color_key = Color::red;

	y = config::game::score_position_y;
}

void Score::draw(void) {
	// Count score ciphers.
	int ciphers = 0;
	uint32_t s = score;

	do {
		s /= 10;
		ciphers++;
	} while (s > 0);

	// Calculate the total width.
	const int number_width = static_cast<double>(numbers.size.width) / 10;
	const int width = number_width * ciphers;
	
	// Calculate the X position.
	const double start_x = (config::screen::width - width) / 2;
	const double final_x = start_x + width;

	// Draw each number.
	s = score;

	Rect2d draw_rect{ 0, 0, number_width, numbers.size.height };
	Rect2d screen_rect{ 0, config::game::score_position_y, width, numbers.size.height };

	for (int x = start_x, c = ciphers; c > 0; x += number_width, c--) {
		const double value = std::pow(10, c - 1);
		const int number = s / value;
		s -= number * value;

		draw_rect.x = number * number_width;
		screen_rect.x = x;

		Console::getInstance()->draw(numbers, draw_rect, screen_rect);
	}

}

void Score::increment(void) {
	score++;
}

void Score::restart(void) {
	score = 0;
}
