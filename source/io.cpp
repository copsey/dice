#include <iostream>
#include <limits>

#include "util/math.hpp"
#include "util/numeric.hpp"
#include "util/string.hpp"

#include "info.hpp"
#include "io.hpp"

using std::vector;
using std::string;
using std::ostream;
using std::cout;
using std::cerr;

using int_limits = std::numeric_limits<int>;

using namespace dice;

ostream & dice::operator<<(ostream & os, const Die & d) {
	return os << 'd' << d.sides();
}

ostream & dice::operator<<(ostream & os, const vector<Die> & dice) {
	if (dice.empty()) return os;

	os << dice.front();
	for (auto i = dice.begin() + 1; i != dice.end(); ++i) {
		os << ' ' << *i;
	}
	return os;
}

void dice::write_die_roll(const Die & d, Die::result_type roll, ostream & os) {
	auto max_roll = d.sides();
	
	auto str = std::to_string(roll);
	auto len = util::num_digits(max_roll);
	util::pad_front(str, ' ', len);
	
	os << str;
}

void dice::write_dice_roll_sum(const vector<Die> & dice, const vector<Die::result_type> & roll, ostream & os) {
	auto sum = util::sum(roll);
	Die::result_type max_sum = 0;
	for (auto & d: dice) max_sum += d.sides();
	
	auto str = std::to_string(sum);
	auto len = util::num_digits(max_sum);
	util::pad_front(str, ' ', len);
	
	os << str;
}

void dice::print_chosen_dice(const vector<Die> & dice) {
	if (dice.empty()) {
		cout << "(no dice chosen)\n";
	} else {
		cout << dice << "\n";
	}
}

void dice::print_default_dice(const vector<Die> & dice) {
	if (dice.empty()) {
		cout << "(default choice: no dice)\n";
	} else {
		cout << "(default choice: " << dice << ")\n";
	}
}

void dice::print_dice_roll(const vector<Die> & dice, const vector<Die::result_type> & roll, bool verbose) {
	if (verbose) {
		switch (roll.size()) {
		case 0:
			cout << "0\n";
			break;
			
		case 1:
			write_die_roll(dice[0], roll[0], cout);
			cout << "\n";
			break;
			
		default:
			{
				write_die_roll(dice[0], roll[0], cout);
				
				for (typename vector<Die>::size_type i = 1; i < dice.size(); ++i) {
					cout << " + ";
					write_die_roll(dice[i], roll[i], cout);
				}
				
				cout << " = ";
				write_dice_roll_sum(dice, roll, cout);
				cout << "\n";
				break;
			}
		}
	} else {
		if (roll.size() > 0) {
			cout << roll[0];
			for (auto r = roll.begin() + 1; r != roll.end(); ++r) cout << " " << *r;
			cout << "\n";
		}
	}
}

void dice::print_program_help() {
	cout << "Press ENTER with a blank input to roll the dice.\n"
			"Enter 'c n1 n2 ...' to choose a new set of dice to roll,\n"
			"  where n1, n2, ... are the number of sides on the dice.\n"
			"Enter 'l' to list the chosen dice.\n"
			"Enter 'h' to display this help message.\n"
			"Enter 'q' to quit the program.\n";
}

void dice::print_invalid_input() {
	cerr << "Your input could not be recognised.\n"
			"Enter 'h' for help.\n";
}

void dice::print_cl_help() {
	cout << "Usage: dice [options] [<number-of-sides> ...]\n"
			"\n"
			"Options:\n"
			"  [-? | --help]         print this help message, then quit\n"
			"  [-# | --version]      print the version of this program, then quit\n"
			"  [-q | --quiet]        suppress output to just the rolls\n"
			"  [-v | --verbose]      show extra information (default)\n"
			"  [--rolls=N]           roll the dice N times, then quit\n"
			"\n"
			"Examples:\n"
			"  dice: start with a d6\n"
			"  dice 6 6: start with two d6's\n"
			"  dice 20: start with a d20\n";
}

void dice::print_version() {
	cout << "dice v" << version_c_str << "\n";
	cout << "Copyright (c) 2016-2021 Jack Copsey\n";
}

void dice::print_invalid_clo(const string & str) {
	cerr << str << " is not a valid option.\n"
		<< "Use \"dice --help\" to see a list of all available options.\n";
}

bool dice::read_die(const string & str, vector<Die> & dice) {
	auto success = false;
	
	try {
		dice.emplace_back(util::to_i(str));
		success = true;
	} catch (std::invalid_argument &) {
		cerr << "'" << str << "' is not an integer.\n";
	} catch (std::out_of_range &) {
		cerr << str << " is too many sides for a die. Maximum number of sides is "
			<< int_limits::max() << ".\n";
	} catch (Die::bad_num_sides & ex) {
		cerr << "Expected zero or more sides, got " << ex.n << ".\n";
	}
	
	return success;
}
