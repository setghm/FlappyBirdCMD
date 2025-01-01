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

		constexpr double gravity = 45;

		constexpr double tubes_start_x = screen::width * 1.2;
		constexpr double tubes_min_space = 22;
		constexpr double tubes_max_space = 24;
		constexpr double tubes_min_middle_y = screen::height * 0.375;
		constexpr double tubes_max_middle_y = screen::height * 0.625;
		constexpr double tubes_velocity = -40;

		constexpr double bg_velocity = -5;

		constexpr double score_position_y = screen::height * 0.05;

		constexpr double title_y = screen::height * 0.25;
		constexpr double start_label_y = screen::height * 0.75;

		constexpr double duration_tubes_generation = 1.8; // In seconds
		constexpr double duration_blink = 1; // In seconds
	};

	namespace player {
		constexpr double start_x = screen::width * 0.1;
		constexpr double start_y = screen::height * 0.25;
		constexpr double jump_velocity = -40;
	};
};
