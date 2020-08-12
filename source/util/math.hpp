#ifndef DICE_UTIL_MATH
#define DICE_UTIL_MATH

namespace dice {
	namespace util {
		/// Compute the number of digits that `x` has when written in base 10.
		///
		/// 0 is defined to have 0 digits, and the sign of `x` is ignored.
		template <typename Integer>
		Integer num_digits(Integer x) {
			Integer n{0};
			while (x != 0) { x /= 10; ++n; }
			return n;
		}
	}
}

#endif
