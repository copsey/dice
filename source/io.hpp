#ifndef DICE_IO
#define DICE_IO

#include <ostream>
#include <string>
#include <vector>

#include "die.hpp"

namespace dice {
   /// Write `d` to `os` in the form "dN", where N is the number of sides of
   /// `d`.
   std::ostream & operator<< (std::ostream & os, const Die & d);

   /// Write `dice` to `os` as a list in the form "dn1 dn2 ...".
   std::ostream & operator<< (std::ostream & os, const std::vector<Die> & dice);

   /// Print the chosen set of dice.
   void print_chosen_dice (const std::vector<Die> & dice);

   /// Print the default set of dice.
   void print_default_dice (const std::vector<Die> & dice);

   /// Print the given dice roll and its sum.
   void print_dice_roll (const std::vector<Die::result_type> & roll);

   /// Print help related to the interface within the program.
   void print_program_help ();

   /// Print help related to the command-line interface.
   void print_cl_help ();

   /// Print the version of the program.
   void print_version ();

   /// Print an error message indicating that an invalid string was input into
   /// the program.
   void print_invalid_input ();

   /// Print an error message indicating that `str` is not a command-line
   /// option.
   void print_invalid_clo (const std::string & str);

   /// Convert `str` to an `int` and append a new die to the end of `dice` with
   /// that many sides.
   ///
   /// An error message is printed if this fails for some reason. In this case,
   /// `dice` remains in the same state as before the function was called.
   ///
   /// @returns whether the function succeeded.
   bool read_die (const std::string & str, std::vector<Die> & dice);
}

#endif
