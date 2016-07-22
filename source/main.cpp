#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "util/cli.hpp"
#include "util/string.hpp"

#include "die.hpp"
#include "io.hpp"
#include "random.hpp"

using namespace dice;

/// Roll each of the given dice.
///
/// @returns a vector containing each roll, in the same order as the
/// corresponding dice.
std::vector<Die::result_type> roll_dice(const std::vector<Die> & dice) {
   std::vector<Die::result_type> roll{};
   for (auto & d: dice) roll.push_back(d());
   return roll;
}

/// Roll each of the given dice and print the result.
void roll_dice_and_print(const std::vector<Die> & dice) {
   auto roll = roll_dice(dice);
   print_dice_roll(dice, roll);
}

int main(int arg_c, const char * arg_v[]) {
   std::vector<Die> dice{};
   bool quit = false;

   // process command-line input
   {
      auto args = util::encapsulate_args(arg_c, arg_v);

      // process command-line options
      for (int i = 1; i < arg_c; ++i) {
         auto & arg = args[i];

         if (util::is_clo(arg)) {
            if (arg == "-h" || arg == "--help") {
               print_cl_help();
               return 0;
            } else if (arg == "-v" || arg == "--version") {
               print_version();
               return 0;
            } else if (arg == "-1" || arg == "--once") {
               quit = true;
            } else {
               print_invalid_clo(arg);
               return 1;
            }
         }
      }

      // read initial choice of dice
      bool success = true;

      for (int i = 1; i < arg_c; ++i) {
         auto & arg = args[i];

         if (!util::is_clo(arg)) {
            if (!read_die(arg, dice)) success = false;
         }
      }

      if (!success) {
         std::cerr << "(try 'dice --help' if you're stuck)\n";
         return 2;
      }
   }

   if (dice.empty()) {
      dice.emplace_back(6);
      print_default_dice(dice);
   }

   seed();

   roll_dice_and_print(dice);

   while (!quit) {
      std::string input;
      std::getline(std::cin, input);

      auto commands = util::split_and_prune(input);

      if (commands.empty() || commands[0] == "r" || commands[0] == "roll") {
         roll_dice_and_print(dice);
      } else if (commands[0] == "q" || commands[0] == "quit" || commands[0] == "exit") {
         quit = true;
      } else if (commands[0] == "h" || commands[0] == "help") {
         print_program_help();
      } else if (commands[0] == "l" || commands[0] == "list") {
         print_chosen_dice(dice);
      } else if (commands[0] == "c" || commands[0] == "choose") {
         std::vector<Die> new_dice{};
         auto success = true;

         for (auto i = commands.begin() + 1; i != commands.end(); ++i) {
            auto & str = *i;

            if (!read_die(str, new_dice)) success = false;
         }

         if (success) {
            dice = std::move(new_dice);
            roll_dice_and_print(dice);
         }
      } else {
         print_invalid_input();
      }
   }
}
