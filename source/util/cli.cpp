#include "cli.hpp"

using std::string_view;
using std::vector;

vector<string_view> dice::util::encapsulate_args(int arg_c, char const* arg_v[]) {
	auto args = vector<string_view>{};
	for (int i = 0; i < arg_c; ++i) args.emplace_back(arg_v[i]);
	return args;
}

bool dice::util::is_clo(string_view str) {
	return !str.empty() && str.front() == '-';
}
