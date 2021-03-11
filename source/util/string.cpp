#include <cctype>
#include <cstddef>
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

int dice::util::to_i(string_view str, int base) {
	std::size_t pos;

	auto s = string{str};
	auto i = std::stoi(s, &pos, base);
	
	if (pos < s.size()) {
		throw std::invalid_argument{"dice::util::to_i: excess chars"};
	}
	
	return i;
}

void dice::util::pad_front(string & str, char ch, string::size_type min_l) {
	str.insert(0, (str.size() < min_l) ? (min_l - str.size()) : 0, ch);
}
