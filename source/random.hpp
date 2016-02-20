#ifndef DICE_RANDOM
#define DICE_RANDOM

#include <random>

namespace dice {
   /// A `mt19937` used as the random number engine when rolling dice.
   ///
   /// This should be seeded at some point before use.
   extern std::mt19937 rand_eng;

   /// Seed `rand_eng` with a value from a `random_device`.
   void seed ();
}

#endif
