#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "util/cli.hpp"
#include "util/regex.hpp"
#include "util/string.hpp"

#include "die.hpp"
#include "io.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::move;
using std::string;
using std::string_view;
using std::vector;

using optional_int = std::optional<int>;

using namespace dice;

using util::as_string_view;
using util::regex_match;
using util::sv_match;

/// Roll each of the given dice.
///
/// @returns a vector containing each roll, in the same order as the
/// corresponding dice.
vector<die::result_type> roll_dice(vector<die> const& dice) {
	vector<die::result_type> roll;
	for (auto & d : dice) roll.push_back(d());
	return roll;
}

/// Roll each of the given dice and print the result.
void roll_dice_and_print(vector<die> const& dice, bool verbose) {
	auto roll = roll_dice(dice);
	print_dice_roll(dice, roll, verbose);
}

/// Apply the effects of the command line options. Any other input is ignored.
int process_options(vector<string_view> const& args,
	optional_int & num_rolls, bool & quit, bool & verbose)
{
	int status = 0;
	string_view basename = args[0];

	for (int i = 1; i < args.size(); ++i) {
		string_view arg = args[i];

		if (arg == "-?" || arg == "--help") {
			print_cl_help(basename);
			quit = true;
			break;
		} else if (arg == "-#" || arg == "--version") {
			print_version();
			quit = true;
			break;
		} else if (arg == "-q" || arg == "--quiet") {
			verbose = false;
		} else if (arg=="-v" || arg=="--verbose") {
			verbose = true;
		} else if (sv_match match; regex_match(arg, match, regex::rolls_option)) {
			auto str = as_string_view(match[1]);
			auto success = read_num_rolls(str, num_rolls, arg, basename);

			if (!success) {
				status = 1;
				break;
			}
		} else if (util::is_clo(arg)) {
			print_invalid_clo(arg, basename);
			status = 1;
			break;
		}
	}

	return status;
}

/// Read the initial choice of dice. Any options are ignored.
int process_choice_of_dice(vector<string_view> const& args, vector<die> & dice) {
	int status = 0;
	string_view basename = args[0];
	
	for (int i = 1; i < args.size(); ++i) {
		string_view arg = args[i];
		
		if (!util::is_clo(arg)) {
			if (!read_die(arg, dice)) status = 2;
		}
	}

	if (status != 0) print_help_message_hint(basename);
	return status;
}

/// Process user input during interactive mode.
void handle_input(string_view input, vector<die> & dice, bool & quit, bool verbose) {
	auto commands = util::split_and_prune(input);
	
	if (commands.empty() || commands[0] == "r" || commands[0] == "roll") {
		roll_dice_and_print(dice, verbose);
	} else if (commands[0] == "q" || commands[0] == "quit" || commands[0] == "exit") {
		quit = true;
	} else if (commands[0] == "h" || commands[0] == "help" || commands[0] == "?") {
		print_program_help();
	} else if (commands[0] == "l" || commands[0] == "list") {
		print_chosen_dice(dice);
	} else if (commands[0] == "c" || commands[0] == "choose") {
		vector<die> new_dice;
		bool success = true;
		
		for (auto i = commands.begin() + 1; i != commands.end(); ++i) {
			string_view str = *i;
			
			if (!read_die(str, new_dice)) success = false;
		}
		
		if (success) {
			dice = move(new_dice);
			roll_dice_and_print(dice, verbose);
		}
	} else {
		print_invalid_input();
	}
}

int main(int arg_c, char const* arg_v[]) {
	vector<die> dice;
	optional_int num_rolls;
	bool quit = false;
	bool verbose = true;

	// Process input to the program.

	auto args = util::encapsulate_args(arg_c, arg_v);

	if (int status = process_options(args, num_rolls, quit, verbose); status != 0) {
		return status;
	}

	if (int status = process_choice_of_dice(args, dice); status != 0) {
		return status;
	}

	// Quit now if requested.

	if (quit) return 0;

	// Choose a default set of dice if none were specified by the user.
	
	if (dice.empty()) {
		dice.emplace_back(6);
		print_default_dice(dice, verbose);
	}

	// Set a seed for the random engine.
	
	seed();

	// Either roll the dice the requested number of times and immediately quit,
	// or roll the dice once and wait for further input.
	
	if (num_rolls) {
		for (int i = 0; i < *num_rolls; ++i) roll_dice_and_print(dice, verbose);
		quit = true;
	} else {
		roll_dice_and_print(dice, verbose);
	}

	// The main loop ...
	
	while (!quit) {
		cout << ">>> ";

		/// Handle the user input.
		/// Stop program execution when the input is empty.
		
		if (string input; getline(cin, input)) {
			handle_input(input, dice, quit, verbose);
		} else {
			cout << endl;
			quit = true;
		}
	}
}
