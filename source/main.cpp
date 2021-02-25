#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "util/cli.hpp"
#include "util/string.hpp"

#include "die.hpp"
#include "io.hpp"
#include "random.hpp"

using std::string;
using std::vector;
using std::move;
using std::cin;
using std::cout;
using std::cerr;
using std::getline;
using std::endl;
using std::regex;
using std::regex_match;
using std::smatch;

using namespace dice;

/// Roll each of the given dice.
///
/// @returns a vector containing each roll, in the same order as the
/// corresponding dice.
vector<Die::result_type> roll_dice(const vector<Die> & dice) {
	vector<Die::result_type> roll{};
	for (auto & d: dice) roll.push_back(d());
	return roll;
}

/// Roll each of the given dice and print the result.
void roll_dice_and_print(const vector<Die> & dice, bool verbose) {
	auto roll = roll_dice(dice);
	print_dice_roll(dice, roll, verbose);
}

int main(int arg_c, const char * arg_v[]) {
	vector<Die> dice{};
	int num_rolls = -1;
	bool verbose = true;
	
	// process command-line input
	{
		auto args = util::encapsulate_args(arg_c, arg_v);
		
		// process command-line options
		for (int i = 1; i < arg_c; ++i) {
			auto & arg = args[i];
			
			if (util::is_clo(arg)) {
				if (arg == "-?" || arg == "--help") {
					print_cl_help();
					return 0;
				}
				
				if (arg == "-#" || arg == "--version") {
					print_version();
					return 0;
				}
				
				if (arg == "-q" || arg == "--quiet") {
					verbose = false;
					continue;
				}
				
				if (arg=="-v" || arg=="--verbose") {
					verbose = true;
					continue;
				}
				
				{
					regex re{"(?:--rolls=)(.*)"};
					smatch m{};
					
					if (regex_match(arg, m, re)) {
						int n;
						string str = m[1].str();
						
						try {
							n = util::to_i(str);
						} catch (std::invalid_argument &) {
							cerr << "Error: could not process option '" << arg << "'\n"
								<< "The string '" << str << "' is not an integer!\n"
								<< "(try 'dice --help' if you're stuck)\n";
							return 1;
						} catch (std::out_of_range &) {
							cerr << "Error: could not process option '" << arg << "'\n"
								<< "The number '" << str << "' is too big to store!\n"
								<< "(try 'dice --help' if you're stuck)\n";
							return 1;
						}
						
						if (n < 0) {
							cerr << "Error: could not process option '" << arg << "'\n"
								<< "Cannot roll dice " << n << " times!\n"
								<< "(try 'dice --help' if you're stuck)\n";
							return 1;
						}
						
						num_rolls = n;
						continue;
					}
				}
				
				print_invalid_clo(arg);
				return 1;
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
			cerr << "(try 'dice --help' if you're stuck)\n";
			return 2;
		}
	}
	
	if (dice.empty()) {
		dice.emplace_back(6);
		if (verbose) print_default_dice(dice);
	}
	
	seed();
	
	if (num_rolls != -1) {
		for (int i = 0; i < num_rolls; ++i) roll_dice_and_print(dice, verbose);
		return 0;
	}
	
	roll_dice_and_print(dice, verbose);
	
	for (bool quit = false; !quit; ) {
		string input;
		cout << ">>> ";
		
		if (!getline(cin, input)) {
			cout << endl;
			break;
		}
		
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
			vector<Die> new_dice{};
			auto success = true;
			
			for (auto i = commands.begin() + 1; i != commands.end(); ++i) {
				auto & str = *i;
				
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
}
