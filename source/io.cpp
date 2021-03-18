#include <iostream>
#include <limits>

#include "util/math.hpp"
#include "util/numeric.hpp"
#include "util/string.hpp"

#include "info.hpp"
#include "io.hpp"

using int_limits = std::numeric_limits<int>;

using namespace dice;

std::ostream & dice::operator<< (std::ostream & out, std::vector<die> const& dice) {
	if (dice.empty()) return out;

	out << dice.front();
	for (auto i = dice.begin() + 1; i != dice.end(); ++i) {
		out << ' ' << *i;
	}
	return out;
}

void dice::write_die_roll(die const& d, die::result_type roll, std::ostream & out) {
	auto max_roll = d.sides();
	
	auto str = std::to_string(roll);
	auto len = util::num_digits(max_roll);
	util::pad_front(str, ' ', len);
	
	out << str;
}

void dice::write_dice_roll_sum(std::vector<die> const& dice, std::vector<die::result_type> const& roll, std::ostream & out) {
	auto sum = util::sum(roll);
	die::result_type max_sum = 0;
	for (auto & d: dice) max_sum += d.sides();
	
	auto str = std::to_string(sum);
	auto len = util::num_digits(max_sum);
	util::pad_front(str, ' ', len);
	
	out << str;
}

void dice::print_chosen_dice(std::vector<die> const& dice) {
	if (dice.empty()) {
		std::cout << "(no dice chosen)\n";
	} else {
		std::cout << dice << "\n";
	}
}

void dice::print_default_dice(std::vector<die> const& dice, bool verbose) {
	if (verbose) {
		if (dice.empty()) {
			std::cout << "(default choice: no dice)\n";
		} else {
			std::cout << "(default choice: " << dice << ")\n";
		}
	}
}

void dice::print_dice_roll(std::vector<die> const& dice, std::vector<die::result_type> const& roll, bool verbose) {
	if (verbose) {
		switch (roll.size()) {
		case 0:
			std::cout << "0\n";
			break;
			
		case 1:
			write_die_roll(dice[0], roll[0], std::cout);
			std::cout << "\n";
			break;
			
		default:
			{
				write_die_roll(dice[0], roll[0], std::cout);
				
				for (typename std::vector<die>::size_type i = 1; i < dice.size(); ++i) {
					std::cout << " + ";
					write_die_roll(dice[i], roll[i], std::cout);
				}
				
				std::cout << " = ";
				write_dice_roll_sum(dice, roll, std::cout);
				std::cout << "\n";
				break;
			}
		}
	} else {
		if (roll.size() > 0) {
			std::cout << roll[0];
			for (auto i = roll.begin() + 1; i != roll.end(); ++i) {
				std::cout << " " << *i;
			}
			std::cout << "\n";
		}
	}
}

void dice::print_program_help() {
	std::cout << "Press ENTER with a blank input to roll the dice.\n"
	          << "Enter 'c n1 n2 ...' to choose a new set of dice to roll,\n"
	          << "  where n1, n2, ... are the number of sides on the dice.\n"
	          << "Enter 'l' to list the chosen dice.\n"
	          << "Enter 'h' to display this help message.\n"
	          << "Enter 'q' to quit the program.\n";
}

void dice::print_invalid_input() {
	std::cerr << "Your input could not be recognised.\n"
	          << "Enter 'h' for help.\n";
}

void dice::print_cl_help(std::string_view basename) {
	std::cout << "Usage: " << basename << " <options> [<number-of-sides> ...]\n"
	          << "\n"
	          << "Options:\n"
	          << "  [-? | --help]         Print this help message, then quit.\n"
	          << "  [-# | --version]      Print the version of this program, then quit.\n"
	          << "  [-q | --quiet]        Suppress output to just the rolls.\n"
	          << "  [-v | --verbose]      Show the totals of the rolls and other information\n"
	          << "                        (default).\n"
	          << "  [--rolls=<N>]         Roll the dice <N> times, then quit.\n"
	          << "\n"
	          << "Examples:\n"
	          << "  " << basename << "                  Start with a d6.\n"
	          << "  " << basename << " 6 6              Start with two d6's.\n"
	          << "  " << basename << " 20               Start with a d20.\n";
}

void dice::print_version() {
	std::cout << "dice " << version_c_str << "\n"
              << "Copyright (c) 2016-2021 Jack Copsey\n";
}

void dice::print_nonexistent_option_hint(std::string_view str, std::string_view basename) {
	std::cerr << str << " is not a valid option.\n"
	          << "Use \"" << basename << " --help\" to see a list of all available options.\n";
}

void dice::print_option_use_hint(std::string_view str, std::string_view basename) {
	std::cerr << "This error was caused by " << str << ".\n"
	          << "Use \"" << basename << " --help\" for a description of the options.\n";
}

void dice::print_help_message_hint(std::string_view basename) {
	std::cerr << "Try \"" << basename << " --help\" for some example uses.\n";
}

std::optional<die> dice::read_die(std::string_view str)
{
	std::optional<die> d;

	try {
		int sides;
		util::from_chars(str, sides);
		d.emplace(sides);
	} catch (std::invalid_argument &) {
		std::cerr << "'" << str << "' is not an integer.\n";
	} catch (std::out_of_range &) {
		std::cerr << str << " is too many sides for a die. Maximum number of sides is " << int_limits::max() << ".\n";
	} catch (die::bad_num_sides & ex) {
		std::cerr << "Expected one or more sides, got " << ex.n << ".\n";
	}
	
	return d;
}

std::optional<int> dice::read_num_rolls(std::string_view str)
{
	std::optional<int> num_rolls;

	try {
		int i;
		util::from_chars(str, i);

		if (i < 0) {
			std::cerr << "Expected zero or more rolls, got " << i << ".\n";
		} else {
			num_rolls = i;
		}
	} catch (std::invalid_argument &) {
		std::cerr << "'" << str << "' is not an integer.\n";
	} catch (std::out_of_range &) {
		std::cerr << "Maximum number of rolls is " << int_limits::max() << ".\n";
	}

	return num_rolls;
}
