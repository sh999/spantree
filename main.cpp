// main.py
// Simulate bridge forwarding behavior
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include "Commands.h"
#include "Config_Message.h"
#include "Bridge.h"
#include "Network.h"
using namespace std;

int main(){
	ifstream lan_input;
	ifstream commands_input;
	lan_input.open("./lan3");
	commands_input.open("./commands3");
	Network network(lan_input);
	Commands commands(commands_input);
	// cout << "Network and commands after parsing:\n";
	cout << "---------------\n";
	cout << "Original network:\n";
	network.print_network();
	// cout << "Commands:\n";
	// commands.print_commands();
	cout << "Running messages\n";
	network.run_commands(commands);		// Run all commands
	network.change_ports();				// Decide to keep open or close ports for all bridges
	cout << "End messages. New network\n";
	network.print_network();
	lan_input.close();
	commands_input.close();
	cout << "end\n";
}
