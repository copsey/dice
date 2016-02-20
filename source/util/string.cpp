#include <cctype>
#include <cstddef>
#include <stdexcept>

#include "string.hpp"

std::vector<std::string> dice::util::split_and_prune (const std::string & str) {
   std::vector<std::string> substrings;

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

int dice::util::to_i (const std::string & str, int base) {
   std::size_t pos;
   auto i = std::stoi(str, &pos, base);

   if (pos < str.size()) {
      throw std::invalid_argument{"dice::to_i: excess chars"};
   }

   return i;
}
