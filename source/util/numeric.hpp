#ifndef DICE_UTIL_NUMERIC
#define DICE_UTIL_NUMERIC

#include <numeric>

namespace dice {
	namespace util {
		/// Calculate the sum of the elements in `c`, starting from 0.
		template <typename Container>
		auto sum(Container const& c) -> typename Container::value_type
		{
			auto zero = typename Container::value_type {0};
			return std::accumulate(c.begin(), c.end(), zero);
		}
	}
}

#endif
