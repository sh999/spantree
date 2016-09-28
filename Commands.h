#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
struct Commands{
	vector<string> all_commands;
	Commands(ifstream& input_file);
	vector<string> parse_input(ifstream& input_file);	// From string of numbers, make list of numbers
	void print_commands();
	vector<string> get_commands();
};
#endif