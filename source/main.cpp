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
void roll_dice_and_print(const std::vector<Die> & dice, bool verbose) {
	auto roll = roll_dice(dice);
	print_dice_roll(dice, roll, verbose);
}

int main(int arg_c, const char * arg_v[]) {
	std::vector<Die> dice{};
	int num_rolls = -1;
	bool verbose = true;
	
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
				}
				
				if (arg == "-v" || arg == "--version") {
					print_version();
					return 0;
				}
				
				if (arg == "-q" || arg == "--quiet") {
					verbose = false;
					continue;
				}
				
				if (arg=="-l" || arg=="--loud" || arg=="--verbose") {
					verbose = true;
					continue;
				}
				
				{
					std::regex re{"(?:-r|--rolls=)(.*)"};
					std::smatch m{};
					
					if (std::regex_match(arg, m, re)) {
						int n;
						std::string str = m[1].str();
						
						try {
							n = util::to_i(str);
						} catch (std::invalid_argument &) {
							std::cerr << "Error: could not process option '" << arg << "'\n"
								<< "The string '" << str << "' is not an integer!\n"
								<< "(try 'dice --help' if you're stuck)\n";
							return 1;
						} catch (std::out_of_range &) {
							std::cerr << "Error: could not process option '" << arg << "'\n"
								<< "The number '" << str << "' is too big to store!\n"
								<< "(try 'dice --help' if you're stuck)\n";
							return 1;
						}
						
						if (n < 0) {
							std::cerr << "Error: could not process option '" << arg << "'\n"
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
			std::cerr << "(try 'dice --help' if you're stuck)\n";
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
		std::string input;
		std::cout << ">>> ";
		std::getline(std::cin, input);
		
		auto commands = util::split_and_prune(input);
		
		if (commands.empty() || commands[0] == "r" || commands[0] == "roll") {
			roll_dice_and_print(dice, verbose);
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
				roll_dice_and_print(dice, verbose);
			}
		} else {
			print_invalid_input();
		}
	}
}
