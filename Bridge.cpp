#include "Bridge.h"

	Bridge::Bridge(string line){
		// cout << "Creating bridge..\n";
		istringstream line_stream(line);
		int counter = 0;
		string s;
		line_stream >> s;
		bridge_id = stoi(s);
		config_message = Config_Message(get_bridge_id(), 0, get_bridge_id());
	}

	void Bridge::connect_bridge_with_lans(string line){
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

	void Bridge::receive_message(Config_Message received_msg){		// Deal with message sent by another bridge
		bool changed = false;
		cout << "\n\t\t\tBridge " << get_bridge_id() << " ";
		config_message.print_config();
		cout << " has received message: ";
		received_msg.print_config();
		if(received_msg.get_root() < config_message.get_root()){		// If received message has lower root, set new root and root distance
			cout << "\n\t\t\t\tSmaller root seen.  Changing root and distance\n";
			config_message.set_root(received_msg.get_root());
			config_message.set_dist_root(received_msg.get_dist_root()+1);
			cout << "\t\t\t\tSet config message to ";
			config_message.print_config();
			cout << endl;
			changed = true;
		}
		else if (received_msg.get_root() == config_message.get_root()){	// Else if same root but different dist to root or different sender #
			// cout << "\n\t\t\t\tsame root seen\n";
			if(received_msg.get_dist_root()+1 < config_message.get_dist_root()){
				cout << "\n\t\t\t\tDist+1 is smaller\n";
				config_message.set_dist_root(received_msg.get_dist_root()+1);
				changed = true;
			}
			else{
				changed = false;
			}
			if(changed){													// this boolean is for display purposes only
				cout << "\n\t\t\t\tChanging config message to ";
			}
			else{
				cout << "\n\t\t\t\tNot changing own config message ";
			}
			config_message.print_config();
			cout << endl;
		}
		check_port(received_msg);
	}
	void Bridge::check_port(Config_Message received_msg){
		int port = received_msg.get_sender();
		cout << "\n\t\t\t\tChecking if msg "; received_msg.print_config(); 
		cout << " is best for port " << port; best_msg_on_ports[port].print_config(); cout << endl;
		if(received_msg.get_root() < best_msg_on_ports[port].get_root()){
			best_msg_on_ports[port] = received_msg;
			cout << "\t\t\t\tReceived msg is better than previous\n";
		}
		else if(received_msg.get_root() == best_msg_on_ports[port].get_root()){
			cout << "same root\n";
		}
	}
	void Bridge::add_neighbors(Bridge b){
		// Add neighboring bridges (having same lans) to current bridge
		// other_bridges.push_back(b);
		other_bridges.insert(b.get_bridge_id());
		Config_Message c(999,999,999);
		best_msg_on_ports[b.get_bridge_id()] = c;
	}
	int Bridge::get_bridge_id(){
		return bridge_id;
	}

	void Bridge::send_bridge(){
		cout << "\tSending from bridge"<< bridge_id << endl;
		cout << "\t\tThis bridge's config:\n\t\t";
		config_message.print_config();
	}

	Config_Message Bridge::get_message(){
		return config_message;
	}

	void Bridge::print_bridge(){
		cout << "Bridge #"<< bridge_id << ":";
		config_message.print_config();
		cout << endl;
		cout << "\tLANs:\n";
		for(int i = 0; i < lans.size(); i++){
			cout << "\t\t" << lans[i] << endl;
		}
		cout << "\tNeighbors:\n";
		for(int id: other_bridges){
			cout << "\t\t" << id << endl;
		}
		cout << "\tBest port msg's:\n";
		typedef map<int, Config_Message>::iterator it;
		for(it i = best_msg_on_ports.begin(); i != best_msg_on_ports.end(); i++){
			cout << "\t\tFrom port/link to bridge " << i->first << ":";
			i->second.print_config();
			cout << endl;
		}
	}
