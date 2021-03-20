#ifndef DICE_DIE
#define DICE_DIE

#include "random.hpp"

namespace dice {
	struct die {
		/// The type of value returned when the die is rolled.
		using result_type = int;
		
		/// Construct a six-sided die.
		die() = default;
		
		/// Construct an `n`-sided die.
		///
		/// @pre `n` must be greater than zero.
		die(result_type n)
		: dist{1, n}
		{ 
			assert(n > 0);
		}
		 
		/// The number of sides that the die has.
		result_type sides() const { return dist.max(); }
		
		/// Roll the die.
		result_type operator() () const { return dist(rand_eng); }
		
	private:
		mutable std::uniform_int_distribution<result_type> dist{1, 6};
	};
}

#endif
