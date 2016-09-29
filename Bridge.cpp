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
	void Bridge::receive_message(Config_Message sender_message){
		//CHECKPOINT:  deal w/ message
		cout << "\t\t\tBridge " << get_bridge_id() << " has received message: ";
		sender_message.print_config();
		if(sender_message.get_root() < config_message.get_root()){
			cout << "smaller root seen\n";
			config_message.set_root(sender_message.get_root());
			config_message.set_dist_root(sender_message.get_dist_root()+1);
		}
	}
	void Bridge::add_neighbors(Bridge b){
		// Add neighboring bridges (having same lans) to current bridge
		// other_bridges.push_back(b);
		other_bridges.insert(b.get_bridge_id());
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
	}
