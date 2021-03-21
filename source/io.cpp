#include <iostream>
#include <limits>

#include "util/math.hpp"
#include "util/numeric.hpp"
#include "util/string.hpp"

#include "info.hpp"
#include "io.hpp"

using int_limits = std::numeric_limits<int>;

using namespace dice;

std::optional<die> dice::read_die(std::string_view str)
{
	std::optional<die> d;

	int sides;
	auto result = util::from_chars(str, sides);

	if (result.ec == std::errc::invalid_argument) {
		std::cerr << "'" << str << "' is not an integer.\n";
	} else if (result.ec == std::errc::result_out_of_range) {
		std::cerr << str << " is too many sides for a die. Maximum number of sides is " << int_limits::max() << ".\n";
	} else if (sides <= 0) {
		std::cerr << "Expected one or more sides, got " << sides << ".\n";
	} else {
		d.emplace(sides);
	}
	
	return d;
}

std::optional<int> dice::read_num_rolls(std::string_view str)
{
	std::optional<int> num_rolls;

	int i;
	auto result = util::from_chars(str, i);

	if (result.ec == std::errc::invalid_argument) {
		std::cerr << "'" << str << "' is not an integer.\n";
	} else if (result.ec == std::errc::result_out_of_range) {
		std::cerr << "Maximum number of rolls is " << int_limits::max() << ".\n";
	} else if (i < 0) {
		std::cerr << "Expected zero or more rolls, got " << i << ".\n";
	} else {
		num_rolls = i;
	}

	return num_rolls;
}

std::ostream & dice::operator<< (std::ostream & out, std::vector<die> const& dice) {
	if (dice.empty()) return out;

	out << dice.front();
	for (auto i = dice.begin() + 1; i != dice.end(); ++i) {
		out << ' ' << *i;
	}
	return out;
}

void dice::write_die_roll(std::ostream & out, die const& d, die::result_type roll) {
	auto max_roll = d.sides();
	
	auto str = std::to_string(roll);
	auto len = util::num_digits(max_roll);
	util::pad_front(str, ' ', len);
	
	out << str;
}

void dice::write_dice_roll_sum(std::ostream & out, std::vector<die> const& dice, std::vector<die::result_type> const& rolls) {
	auto sum = util::sum(rolls);
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

void dice::print_dice_roll(std::vector<die> const& dice, std::vector<die::result_type> const& rolls, bool verbose) {
	if (verbose) {
		switch (rolls.size()) {
		case 0:
			std::cout << "0\n";
			break;
			
		case 1:
			write_die_roll(std::cout, dice.front(), rolls.front());
			std::cout << "\n";
			break;
			
		default:
			{	
				for (typename std::vector<die>::size_type i = 0; i < dice.size(); ++i) {
					if (i != 0) std::cout << " + ";
					write_die_roll(std::cout, dice[i], rolls[i]);
				}
				
				std::cout << " = ";
				write_dice_roll_sum(std::cout, dice, rolls);
				std::cout << "\n";
				break;
			}
		}
	} else {
		if (rolls.size() > 0) {
			for (auto iter = rolls.begin(); iter != rolls.end(); ++iter) {
				if (iter != rolls.begin()) std::cout << " ";
				std::cout << *iter;
			}
			std::cout << "\n";
		}
	}
}

void dice::print_program_help() {
	std::cout << "Press ENTER with a blank input to roll the dice.\n"
	          << "Enter 'choose <n1> <n2> ...' to choose a new set of dice to roll,\n"
	          << "  where <n1>, <n2>, ... are the number of sides on the dice.\n"
	          << "Enter 'list' to print the chosen dice.\n"
	          << "Enter 'help' or '?' to print this help message.\n"
	          << "Enter 'quit' or 'exit' to quit the program.\n";
}

void dice::print_invalid_input() {
	std::cerr << "Your input could not be recognised.\n"
	          << "Enter 'help' or '?' for help.\n";
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
