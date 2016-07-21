#include "cli.hpp"

std::vector<std::string> dice::util::encapsulate_args(int arg_c, const char * arg_v[]) {
   std::vector<std::string> args{};
   for (int i = 0; i < arg_c; ++i) args.emplace_back(arg_v[i]);
   return args;
}

bool dice::util::is_clo(const std::string & str) {
   return !str.empty() && str.front() == '-';
}
