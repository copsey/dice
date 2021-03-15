#include <cctype>
#include <charconv>
#include <stdexcept>

#include "string.hpp"

using std::string;
using std::string_view;
using std::vector;

vector<string_view> dice::util::split_and_prune(string_view str) {
	auto substrings = vector<string_view>{};
	
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

void dice::util::from_chars(string_view str, int & value, int base) {
	auto result = std::from_chars(str.begin(), str.end(), value, base);

	if (result.ec == std::errc::invalid_argument) {
		throw std::invalid_argument{"dice::util::from_chars: bad input"};
	}
	
	if (result.ec == std::errc::result_out_of_range) {
		throw std::out_of_range{"dice::util::from_chars: too large to store in int"};
	}
	
	if (result.ptr != str.end()) {
		throw std::invalid_argument{"dice::util::from_chars: excess chars"};
	}
}
