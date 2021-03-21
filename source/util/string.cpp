#include "string.hpp"

#include <cctype>

std::vector<std::string_view> dice::util::split_and_prune(std::string_view str) {
	auto substrings = std::vector<std::string_view>{};
	
	auto i = str.begin();
	auto j = i;
	auto end = str.end();
	
	while (j != end) {
		if (std::isspace(*j)) {
			if (i != j) substrings.emplace_back(i, j-i);
			i = ++j;
		} else {
			++j;
		}
	}
	
	if (i != j) substrings.emplace_back(i, j-i);
	
	return substrings;
}

std::from_chars_result dice::util::from_chars(std::string_view str, int & value, int base)
{
	int new_value;
	auto result = std::from_chars(str.begin(), str.end(), new_value, base);

	// Check for success of std::from_chars. Raise an additional error if
	// not all of the characters in str have been used.

	if (result.ec == std::errc{}) {
		if (result.ptr == str.end()) {
			value = new_value;
		} else {
			result.ec = std::errc::invalid_argument;
		}
	}

	return result;
}
