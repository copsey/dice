#include "random.hpp"

std::mt19937 dice::rand_eng{};
std::random_device rd{};

void dice::seed() {
	rand_eng.seed(rd());
}
