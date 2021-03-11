#ifndef DICE_RANDOM
#define DICE_RANDOM

#include <random>

namespace dice {
	/// A `mt19937` used as the random number engine when rolling dice.
	///
	/// This needs to be seeded at some point before use.
	inline std::mt19937 rand_eng;
	
	/// Seed `rand_eng` with a value from a `random_device`.
	inline void seed() {
		std::random_device rd;
		rand_eng.seed(rd());
	}
}

#endif
