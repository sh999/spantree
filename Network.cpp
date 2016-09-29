#include "Network.h"
	Network::Network(ifstream& input_file){
		cout << "----------------\n";
		cout << "Creating network\n";
		cout << "Parsing input file\n";
		string line;
		while(getline(input_file, line)){
			// cout << "Parsing bridge line: "<< line << endl;  // Parse input file
			Bridge temp_bridge(line);					// Creates bridge obj, which gets set up with its lans
			temp_bridge.connect_bridge_with_lans(line); // Each bridge will have vector of lans it is connected to
			bridges.push_back(temp_bridge);   			// Add to list of bridges in this network
			// create_bridge_network(line);				// After all bridges and respective lans are set up, connect bridges to each other
			record_lans(line);  						// Find unique lan names and associate with bridge
			
		}
		link_neighbors();								// Go through bridges and associate each with neighboring bridges
		cout << "----------------\n";
	}
	
	void Network::record_lans(string line){				// Find unique lan names and associate with bridge
		// cout << "Recording lans...\n";
		istringstream line_stream(line);
		string n;
		int counter = 0;
		while(line_stream >> n){							// For each input file line, obtain only LANs and skip the 1st item (bridge id)
			Bridge some_bridge(line);
			if(counter > 0){	// Skip bridge ID
				// cout << "\tExamining n: " << n << endl;
				lan_map.insert({n,some_bridge});
				lans.push_back(n);
			}
			counter++;
		}
	}
	void Network::create_bridge_network(string line){		// Connect bridges from what lan's they share	
		// cout << "Creating bridge network...\n";
		istringstream line_stream(line);
		string n;
		int counter = 0;
		while(line_stream >> n){							// For each input file line, obtain only LANs and skip the 1st item (bridge id)
			if(counter > 0){	// Skip bridge ID
				// cout << "\tExamining n: " << n << endl;
				lans.push_back(n);
			}
			counter++;
		}
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
		// cout << "From network, finding bridge to send:" << bridge_id << endl;
		get_bridge(bridge_id);
	}
	void Network::get_bridge(int bridge_id){  // Given string ID, return bridge obj. with that id
		for(int i = 0; i < bridges.size(); i++){
			// cout << "get Bridge ID:", b.get_bridge_id()
			// cout << "query id:", bridge_id
			if (bridge_id == bridges[i].get_bridge_id() ){
				// cout << "match"
				bridges[i].send_bridge();
				// bridges[i].get_message();
				for(int id: bridges[i].other_bridges){
					for(int j = 0; j < bridges.size(); j++){
						if(id == bridges[j].get_bridge_id()){
							bridges[j].receive_message(bridges[i].get_message());
						}
					}
				}
				break;
			}
		}
	}

	void Network::change_ports(){
		cout << "Closing/opening ports...\n";
		// Denote "best port" first
		for(int i = 0; i < bridges.size(); i++){   // Loop through each bridge
			cout << "Checking bridge " << bridges[i].get_bridge_id();
			bridges[i].get_message().print_config();
			cout << endl;
			typedef map<int, Config_Message>::iterator bit;
			for(bit p = bridges[i].best_msg_on_ports.begin(); p != bridges[i].best_msg_on_ports.end(); p++){  // Loop through each bridge's ports
				cout << "\tPort: ";
				p->second.print_config();
				if(bridges[i].get_message().get_root() < p->second.get_root()){
					// cout << "p->first:" << p->first << " ";
					cout << ": Own root is smaller. Keep open\n";
					bridges[i].ports_status[p->first] = true;
				}
				else if(bridges[i].get_message().get_root() == p->second.get_root()){
					cout << ": Same root between port and own. ";
					if(bridges[i].get_message().get_dist_root() < p->second.get_dist_root()){
						cout << "Own dist_root is smaller. Keep open";
						bridges[i].ports_status[p->first] = true;

					}
					else if(bridges[i].get_message().get_dist_root() == p->second.get_dist_root()){
						if(bridges[i].get_message().get_sender() < p->second.get_sender()){
							cout << "Same dist from root. Sender ID is smaller. Keep open";
							bridges[i].ports_status[p->first] = true;
						}
					}
				}
				cout << endl;

			}
		}
	}

	void Network::link_neighbors(){												// Link bridges based on what LANs they share
		// cout << "Linking neighboring bridges\n";
		for(int i = 0; i < bridges.size(); i++){								// Loop each bridge
			// cout << "Finding neighbors of bridge ID" << bridges[i].get_bridge_id() << endl;
			for(int j = 0; j < bridges[i].lans.size(); j++){					// Loop each vector of lans for the bridge
				// cout << "\t Looking at lan " << bridges[i].lans[j] << endl;
				for(it k = lan_map.begin(); k != lan_map.end(); k++){			// Loop each lan's associated bridge
					// cout << k->first << "-"  << k->second.get_bridge_id() << endl;
					if(k->first == bridges[i].lans[j] && bridges[i].get_bridge_id() != k->second.get_bridge_id()){  // If LAN name of bridge Y is in bridge X's LAN list and if X, Y are different, add Y as neighbor of X
						// cout <<"Found neighbor\n";
						bridges[i].add_neighbors(k->second);
					}
				}
			}
		}
	}
	void Network::print_network(){
		for(int i = 0; i < bridges.size(); i++){
			bridges[i].print_bridge();
		}
		cout << "Lans:\n";
		for(it i = lan_map.begin(); i != lan_map.end(); i++){
			cout << i->first << "-"  << i->second.get_bridge_id() << endl;
		}
	}

