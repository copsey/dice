#ifndef DICE_UTIL_NUMERIC
#define DICE_UTIL_NUMERIC

#include <numeric>

namespace dice {
   namespace util {
      /// Calculate the sum of the elements in `c`, starting from 0.
      template <class Cont>
      typename Cont::value_type sum (const Cont & c) {
         using T = typename Cont::value_type;
         return std::accumulate(c.begin(), c.end(), T{0});
      }
   }
}

#endif
