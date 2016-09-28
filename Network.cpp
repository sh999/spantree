#include "Network.h"
	Network::Network(ifstream& input_file){
		cout << "Creating network\n";
		parse_input(input_file); 	// Creates bridges and lans
	}
	void Network::parse_input(ifstream& input_file){
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
	void Network::parse_line(string line){
		cout << "parsing line" << line << endl;
		Bridge temp_bridge(line);   	// Creates bridge obj, which gets set up with its lans
		bridges.push_back(temp_bridge);   // Add to list of bridges in this network
		// create_bridge_network();	// After all bridges and respective lans are set up, connect bridges to each other
		record_lans(line); 		// From raw line, keep unique lan names
	}
	void Network::record_lans(string line){
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
	void Network::create_bridge_network(){		// Connect bridges from what lan's they share	
		cout << "Creating bridge network...\n";

	}
	void Network::run_commands(Commands c){
		commands = c.get_commands();
		for(int i = 0; i < commands.size(); i++){
		// for i in commands{
			// cout << "Running command", i;
			find_bridge_and_send(stoi(commands[i]));
		}
	}
	void Network::find_bridge_and_send(int bridge_id){ 	// Send bridge with id i
		cout << "From network, finding bridge to send:" << bridge_id << endl;
		get_bridge(bridge_id);
	}
	void Network::get_bridge(int bridge_id){  // Given string ID, return bridge obj. with that id
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
	void Network::print_network(){
		for(int i = 0; i < bridges.size(); i++){
			bridges[i].print_bridge();
		}
	}

