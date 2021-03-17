#ifndef DICE_IO
#define DICE_IO

#include <optional>
#include <ostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "die.hpp"

namespace dice {
	namespace regex {
		/// A regular expression to parse the number of dice rolls specified
		/// at the command line.
		inline auto const rolls_option = std::regex{"(?:--rolls=)(.*)"};
	}

	/// Write "dN" to `os`, where N is the number of sides of `d`.
	inline std::ostream & operator<< (std::ostream & os, die const& d) {
		return os << 'd' << d.sides();
	}
	
	/// Write `dice` to `os` as a list in the form "dn1 dn2 ...".
	std::ostream & operator<< (std::ostream & os, std::vector<die> const& dice);
	
	/// Write the die roll `r` obtained from `d` to `os`.
	///
	/// Extra spaces are inserted at the front of the outputted text based on the
	/// number of sides of `d`, so that the same number of characters will be
	/// output regardless of which value `r` takes.
	///
	/// `r` should be a valid roll, i.e. obtainable by rolling `d`.
	void write_die_roll(die const& d, die::result_type r, std::ostream & os);
	
	/// Write the sum of the dice rolls in `roll` to `os`.
	///
	/// Extra spaces are inserted at the front of the outputted text based on the
	/// maximum possible sum that can be obtained by rolling the dice in `dice`,
	/// so that the same number of characters will be output regardless of the
	/// rolls that are passed in.
	///
	/// Each `roll[i]` should be obtainable by rolling `dice[i]`.
	/// Furthermore, `dice.size()` and `roll.size()` should be equal.
	void write_dice_roll_sum(std::vector<die> const& dice, std::vector<die::result_type> const& roll, std::ostream & os);
	
	/// Print the chosen set of dice.
	void print_chosen_dice(std::vector<die> const& dice);
	
	/// Print the default set of dice.
	void print_default_dice(std::vector<die> const& dice, bool verbose);
	
	/// Print the given dice roll and its sum.
	///
	/// If `verbose` is true, make the output more user-friendly.
	///
	/// Each `roll[i]` should be obtainable by rolling `dice[i]`.
	/// Furthermore, `dice.size()` and `roll.size()` should be equal.
	void print_dice_roll(std::vector<die> const& dice, std::vector<die::result_type> const& roll, bool verbose);
	
	/// Print help related to the interface within the program.
	void print_program_help();
	
	/// Print help related to the command-line interface.
	void print_cl_help(std::string_view basename);
	
	/// Print the version of the program.
	void print_version();
	
	/// Print an error message indicating that an invalid string was input into
	/// the program.
	void print_invalid_input();
	
	/// Print an error message indicating that `str` is not a command-line
	/// option, and instructions for how to print a list of all available
	/// options.
	void print_nonexistent_option_hint(std::string_view str, std::string_view basename);

	/// Print an error message indicating that there was an issue while trying
	/// to apply the effects of the command-line option contained in `str`,
	/// and instructions for how to print further help on the option.
	void print_option_use_hint(std::string_view str, std::string_view basename);

	/// Print an error message instructing the user how to access the program's
	/// help message from the command line.
	void print_help_message_hint(std::string_view basename);
	
	/// Convert `str` to an `int` and append a new die to the end of `dice` with
	/// that many sides.
	///
	/// An error message is printed if this fails for some reason. In this case,
	/// `dice` remains in the same state as before the function was called.
	///
	/// @returns whether the function succeeded.
	bool read_die(std::string_view str, std::vector<die> & dice);

	/// Convert `str` to an integer and treat this as the number of times to
	/// roll the dice before quitting the program.
	/// 
	/// An error message is printed if this fails, in which case `num_rolls`
	/// remains in the same state as before the function was called.
	/// 
	/// @returns whether the function succeeded.
	bool read_num_rolls(std::string_view str, std::optional<int> & num_rolls);
}

#endif
