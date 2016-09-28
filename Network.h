#ifndef NETWORK_H
#define NETWORK_H
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include "Config_Message.h"
#include "Bridge.h"
#include "Commands.h"
using namespace std;

struct Network{
	vector<Bridge> bridges;
	vector<string> lans;
	// map<string, vector<int>>
	vector<string> commands;
	Network(ifstream& input_file);
	void record_lans(string line);
	void create_bridge_network(string line);
	void run_commands(Commands c);
	void find_bridge_and_send(int bridge_id);
	void get_bridge(int bridge_id);
	void print_network();
};
#endif