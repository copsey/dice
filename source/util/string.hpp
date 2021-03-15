#ifndef DICE_UTIL_STRING
#define DICE_UTIL_STRING

#include <string>
#include <string_view>
#include <vector>

namespace dice {
	namespace util {
		/// Split `str` into the vector of non-empty substrings that are delimited
		/// by whitespace in `str`.
		///
		/// Empty substrings are automatically removed.
		std::vector<std::string_view> split_and_prune(std::string_view str);

		/// Convert `str` into an int, using the given numeric base,
		/// and store the result in `value`.
		///
		/// In addition to throwing the same exceptions as
		/// `std::stoi(str, 0, base)`, a `std::invalid_argument` is thrown if some
		/// unexpected superfluous `char`s were encountered at the end of `str`.
		void from_chars(std::string_view str, int & value, int base = 10);
		
		/// Insert copies of `ch` at the front of `str` until its length is at
		/// least `min_l`.
		///
		/// If `str.size()` is already `min_l` or more, this function has no
		/// effect.
		inline void pad_front(std::string & str, char ch, std::string::size_type min_l = 1)
		{
			str.insert(0, (str.size() < min_l) ? (min_l - str.size()) : 0, ch);
		}
	}
}

#endif
