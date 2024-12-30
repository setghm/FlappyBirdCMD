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

		constexpr double gravity = 25;

		constexpr double tubes_start_x = screen::width * 1.2;
		constexpr double tubes_min_space = 12;
		constexpr double tubes_max_space = 16;
		constexpr double tubes_min_middle_y = screen::height * 0.45;
		constexpr double tubes_max_middle_y = screen::height * 0.55;
		constexpr double tubes_velocity = -30;

		constexpr double duration_tubes_generation = 2.3; // In seconds
	};

	namespace player {
		constexpr double start_x = screen::width * 0.1;
		constexpr double start_y = screen::height * 0.25;
		constexpr double jump_velocity = -28;
	};
};
