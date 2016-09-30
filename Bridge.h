#ifndef BRIDGE_H
#define BRIDGE_H
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include "Config_Message.h"
using namespace std;

struct Bridge{
	int bridge_id;
	vector<string> lans; 			// What LANs are linked to this bridge
	set<int> other_bridges; 		// What other bridges are linked to this bridge 
	map<int, Config_Message> best_msg_on_ports; 	// Best Config message (value) on port int (key)
	map<int, bool> ports_status;	// True/false for all ports on bridge
	Config_Message config_message;
	Bridge(string line);
	void connect_bridge_with_lans(string line);
	void add_neighbors(Bridge);
	void receive_message(Config_Message m);
	void check_port(Config_Message m);		// Check if received msg is better for a given port/link
	void close_ports(vector<int> ports);
	int get_bridge_id();
	void send_bridge();
	void print_bridge(multimap<string, Bridge> lan_map);
	Config_Message get_message();
};
#endif