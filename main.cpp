// main.py
// Simulate bridge forwarding behavior
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Commands{
	vector<string> all_commands;
	Commands(ifstream& input_file){
		cout << "Creating commands\n";
		all_commands = parse_input(input_file);
	}
	vector<string> parse_input(ifstream& input_file){ 	// From string of numbers, make list of numbers
		vector<string> nums;
		string line;
		while(getline(input_file, line)){
			istringstream numstream(line);
			string n;
			while (numstream >> n){
				nums.push_back(n);
			}
			// nums = [int(n) for n in i.split()];
		}
		cout << "Nums:\n";
		for(int i = 0; i < nums.size(); i++){
			cout << nums[i] << endl;
		}
		return nums;
	}
	void print_commands(){
		for(int i = 0; i < all_commands.size(); i++){
			cout << all_commands[i] << endl;
		}
	}
	vector<string> get_commands(){
		return all_commands;
	}
};

struct Config_Message{
	int root;
	int dist_root;
	int sender;
	Config_Message(){

	}
	Config_Message(int x, int y, int z){
		root = x;
		dist_root = y;
		sender = z;
	}
	void print_config(){
		cout << "<"<< root<<","<< dist_root<<","<< sender<<">" << endl;
	}
};
struct Bridge{
	int bridge_id;
	vector<string> lans; // What LANs are linked to this bridge
	vector<Bridge> other_bridges; // What other bridges are linked to this bridge 
	Config_Message config_message;
	Bridge(string line){
		bridge_id = int(line[0]);	// Numeric ID of bridge
		config_message = Config_Message(get_bridge_id(), 0, get_bridge_id());   // Default config message <ID, 0, ID>
		// cout <<  "Line is:x"<< line "x" << endl;
		connect_bridge_with_lans(line);
	}
	void connect_bridge_with_lans(string line){
		for(int i = 1; i < line.length(); i++){
		// for i in range(1,len(line)){	# If see letter, denote as a connected lan to bridge
			// cout << "Looking at item:", line[i]
			if ((line[i] >= 65 && line[i] <= 90) || (line[i] >= 97 && line[i] <= 122)){  // ASCII for letters (lower and uppercase)
				// print ord(line[i])
				lans.push_back(to_string(line[i]));
			}
			else{ 						// If see non-letter, don't update lan
				// cout << ord(line[i])
			}
		}
	}
	int get_bridge_id(){
		return bridge_id;
	}
	void send_bridge(){
		cout << "Sending from bridge"<< bridge_id << endl;
		cout << "Bridge's config:\n";
		config_message.print_config();
	}
	void print_bridge(){
		cout << "Bridge #"<< bridge_id << endl;
		cout << "\tLANs:\n";
		for(int i = 0; i < lans.size(); i++){
			cout << "\t\t" << lans[i] << endl;
		}
	}
};
struct Network{
	vector<Bridge> bridges;
	vector<string> lans;
	vector<string> commands;
	Network(ifstream& input_file){
		cout << "Creating network\n";
		parse_input(input_file); 	// Creates bridges and lans
	}
	void parse_input(ifstream& input_file){
		cout << "parsing input file\n";
		string line;
		while(getline(input_file, line)){
			// parse_line(l)
			Bridge temp_bridge(line);// Creates bridge obj, which gets set up with its lans
			cout << "parsing line"<< line << endl;
			bridges.push_back(temp_bridge);   // Add to list of bridges in this network
			// create_bridge_network();	// After all bridges and respective lans are set up, connect bridges to each other
			record_lans(line);  		// From raw line, keep unique lan names
		}
	}
	void parse_line(string line){
		cout << "parsing line" << line << endl;
		Bridge temp_bridge(line);   	// Creates bridge obj, which gets set up with its lans
		bridges.push_back(temp_bridge);   // Add to list of bridges in this network
		// create_bridge_network();	// After all bridges and respective lans are set up, connect bridges to each other
		record_lans(line); 		// From raw line, keep unique lan names
	}
	void record_lans(string line){
		cout << "Recording lans...\n";
		for(int i = 1; i < line.length(); i++){	// If see letter, denote as a connected lan to bridge
			// cout << "Looking at item:", line[i];
			if ((line[i] >= 65 && line[i] <= 90) || (line[i] >= 97 && line[i] <= 122)){  // ASCII for letters (lower and uppercase)
				// print line[i];
				// print ord(line[i]);
				lans.push_back(to_string(line[i]));
			}
			else{						// If see non-letter, don't update lan
				// print ord(line[i]);
				// continue;
			}
		}
	}
	void create_bridge_network(){		// Connect bridges from what lan's they share	
		cout << "Creating bridge network...\n";

	}
	void run_commands(Commands c){
		commands = c.get_commands();
		for(int i = 0; i < commands.size(); i++){
		// for i in commands{
			// cout << "Running command", i;
			find_bridge_and_send(stoi(commands[i]));
		}
	}
	void find_bridge_and_send(int bridge_id){ 	// Send bridge with id i
		cout << "From network, finding bridge to send:" << bridge_id << endl;
		get_bridge(bridge_id);
	}
	void get_bridge(int bridge_id){  // Given string ID, return bridge obj. with that id
		for(int i = 0; i < bridges.size(); i++){
			// cout << "get Bridge ID:", b.get_bridge_id()
			// cout << "query id:", bridge_id
			if (bridge_id == bridges[i].get_bridge_id() ){
				// cout << "match"
				bridges[i].send_bridge();
				break;
			}
		}
	}
	void print_network(){
		for(int i = 0; i < bridges.size(); i++){
			bridges[i].print_bridge();
		}
	}
};

int main(){
	ifstream lan_input;
	ifstream commands_input;
	lan_input.open("./lan");
	commands_input.open("./com");
	Network network(lan_input);
	Commands commands(commands_input);
	cout << "Network and commands after parsing:\n";
	network.print_network();
	cout << "Commands:\n";
	commands.print_commands();
	cout << "Running simulation\n";
	network.run_commands(commands);
	lan_input.close();
	commands_input.close();
}
