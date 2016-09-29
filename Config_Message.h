#ifndef CONFIG_MESSAGE_H
#define CONFIG_MESSAGE_H
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
struct Config_Message{
	int root;
	int dist_root;
	int sender;
	Config_Message();
	Config_Message(int x, int y, int z);
	void print_config();
	int get_root();
	int get_dist_root();
	int get_sender();
	void set_root(int x);
	void set_dist_root(int x);
	void set_sender(int x);
	
	
};
#endif