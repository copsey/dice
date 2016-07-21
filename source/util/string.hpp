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
      std::vector<std::string> split_and_prune(const std::string & str);

      /// Convert `str` into an `int`, using the given numeric base.
      ///
      /// In addition to throwing the same exceptions as
      /// `std::stoi(str, 0, base)`, a `std::invalid_argument` is thrown if some
      /// unexpected superfluous `char`s were encountered at the end of `str`.
      int to_i(const std::string & str, int base = 10);

      /// Insert copies of `ch` at the front of `str` until its length is at
      /// least `min_l`.
      ///
      /// If `str.size()` is already `min_l` or more, this function has no
      /// effect.
      void pad_front(std::string & str, char ch, std::string::size_type min_l);
   }
}

#endif
