#ifndef DICE_UTIL_STRING
#define DICE_UTIL_STRING

#include <string>
#include <vector>

namespace dice {
   namespace util {
      /// Split `str` into the vector of non-empty substrings that are delimited
      /// by whitespace in `str`.
      ///
      /// Empty substrings are automatically removed.
      std::vector<std::string> split_and_prune (const std::string & str);

      /// Convert `str` into an `int`, using the given numeric base.
      ///
      /// In addition to throwing the same exceptions as `std::stoi(str, 0, base)`,
      /// a `std::invalid_argument` is thrown if some unexpected superfluous
      /// `char`s were encountered at the end of `str`.
      int to_i (const std::string & str, int base = 10);
   }
}

#endif
