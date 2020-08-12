#include "cli.hpp"

using std::vector;
using std::string;

vector<string> dice::util::encapsulate_args(int arg_c, const char * arg_v[]) {
	vector<string> args{};
	for (int i = 0; i < arg_c; ++i) args.emplace_back(arg_v[i]);
	return args;
}

bool dice::util::is_clo(const string & str) {
	return !str.empty() && str.front() == '-';
}
