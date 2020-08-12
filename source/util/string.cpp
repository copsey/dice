#include <cctype>
#include <cstddef>
#include <stdexcept>

#include "string.hpp"

using std::vector;
using std::string;

vector<string> dice::util::split_and_prune(const string & str) {
	vector<string> substrings{};
	
	auto i = str.begin();
	auto j = i;
	auto end = str.end();
	
	while (j != end) {
		if (std::isspace(*j)) {
			if (i != j) substrings.emplace_back(i, j);
			i = ++j;
		} else {
			++j;
		}
	}
	
	if (i != j) substrings.emplace_back(i, j);
	
	return substrings;
}

int dice::util::to_i(const string & str, int base) {
	std::size_t pos;
	auto i = std::stoi(str, &pos, base);
	
	if (pos < str.size()) {
		throw std::invalid_argument{"dice::util::to_i: excess chars"};
	}
	
	return i;
}

void dice::util::pad_front(string & str, char ch, string::size_type min_l) {
	str.insert(0, (str.size() < min_l) ? (min_l - str.size()) : 0, ch);
}
