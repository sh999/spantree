#include "Commands.h"

	Commands::Commands(ifstream& input_file){
		// cout << "Creating commands\n";
		all_commands = parse_input(input_file);
		// cout << "end creating commands\n";
	}
	vector<string> Commands::parse_input(ifstream& input_file){ 	// From string of numbers, make list of numbers
		// cout << "in commands::parse_input\n";
		vector<string> nums;
		string line;
		while(getline(input_file, line)){
			// cout << "Running through commands line\n";
			istringstream numstream(line);
			string n;
			while (numstream >> n){
				nums.push_back(n);
			}
		}
		return nums;

	}
	void Commands::print_commands(){
		for(int i = 0; i < all_commands.size(); i++){
			cout << all_commands[i] << endl;
		}
	}
	vector<string> Commands::get_commands(){
		return all_commands;
	}

