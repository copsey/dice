#ifndef DICE_DIE
#define DICE_DIE

#include <random>

namespace dice {
   struct Die {
      /// The type of integer returned when the die is rolled.
      using result_type = int;

      /// An exception signifying that a die cannot be created with `n` sides.
      struct bad_num_sides { result_type n; };

      /// Make a six-sided die.
      Die() = default;

      /// Make an `n`-sided die.
      ///
      /// @throws `bad_num_sides` if `n` is less than 1.
      Die(result_type n)
       : dist{1, (n > 0) ? n : (throw bad_num_sides{n})} { }

      /// The number of sides that the die has.
      result_type num_sides() const {
         return dist.max();
      }

      /// Roll the die.
      result_type operator()() const;

   private:
      mutable std::uniform_int_distribution<result_type> dist{1, 6};
   };
}

#endif
