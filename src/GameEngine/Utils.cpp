#include "Utils.hpp"
#include <random>

int utils::rand(int min, int max) {
	std::mt19937 rng(std::time(0));
	std::uniform_int_distribution<int> gen(min, max);

	return gen(rng);
}

double utils::rand(double min, double max) {
	std::mt19937 rng(std::time(0));
	std::uniform_real_distribution<double> gen(min, max);

	return gen(rng);
}
