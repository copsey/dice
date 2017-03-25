#include "random.hpp"

std::mt19937 dice::rand_eng{};

void dice::seed() {
	std::random_device rd{};
	rand_eng.seed(rd());
}
