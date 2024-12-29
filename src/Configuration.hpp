#pragma once

#include <string>

namespace config {
	namespace screen {
		constexpr int width = 120;
		constexpr int height = 80;
		constexpr int font_size_x = 4;
		constexpr int font_size_y = 6;
	};

	namespace game {
		const std::wstring name = L"Flappy Bird";

		constexpr double gravity = 20;
	};

	namespace player {
		constexpr double start_x = screen::width * 0.1;
		constexpr double start_y = screen::height * 0.25;
	};
};
