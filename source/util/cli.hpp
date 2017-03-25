#ifndef DICE_UTIL_CLI
#define DICE_UTIL_CLI

#include <string>
#include <vector>

namespace dice {
	namespace util {
		/// Encapsulate the given command-line arguments within a vector of
		/// strings.
		///
		/// It is intended that this function is called with the parameters from
		/// `int main(int arg_c, const char * arg_v[])`, and therefore `arg_v`
		/// should contain `arg_c + 1` entries, with `arg_v[arg_c] == 0`.
		std::vector<std::string> encapsulate_args(int arg_c, const char * arg_v[]);
		
		/// Check whether `str` is formatted as a command-line option.
		///
		/// This is true when `str` has '-' as a prefix.
		bool is_clo(const std::string & str);
	}
}

#endif
