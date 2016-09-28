#ifndef BRIDGE_H
#define BRIDGE_H
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include "Config_Message.h"
using namespace std;

struct Bridge{
	int bridge_id;
	vector<string> lans; // What LANs are linked to this bridge
	vector<Bridge> other_bridges; // What other bridges are linked to this bridge 
	Config_Message config_message;
	Bridge(string line);
	void connect_bridge_with_lans(string line);
	int get_bridge_id();
	void send_bridge();
	void print_bridge();
};
#endif