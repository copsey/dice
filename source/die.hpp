#ifndef DICE_DIE
#define DICE_DIE

#include <random>

namespace dice {
   struct Die {
      /// The type of integer returned when the die is rolled.
      using result_type = int;

      /// An exception signifying that a die cannot be created with `n` sides.
      struct bad_num_sides { int n; };

      /// Make a six-sided die.
      Die() = default;

      /// Make an `n`-sided die.
      ///
      /// @throws `bad_num_sides` if `n` is less than 1.
      Die(int n);

      /// The number of sides that the die has.
      int num_sides() const;

      /// Roll the die.
      int operator()() const;

   private:
      mutable std::uniform_int_distribution<result_type> dist{1, 6};
   };
}

#endif
