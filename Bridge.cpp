#include "Bridge.h"

	Bridge::Bridge(string line){
		cout << "Creating bridge..\n";
		istringstream line_stream(line);
		int counter = 0;
		string s;
		line_stream >> s;
		bridge_id = stoi(s);

		// bridge_id = int(line[0]);	// Numeric ID of bridge
		config_message = Config_Message(get_bridge_id(), 0, get_bridge_id());   // Default config message <ID, 0, ID>
		// cout <<  "Line is:x"<< line "x" << endl;
		// connect_bridge_with_lans(line);
	}
	void Bridge::connect_bridge_with_lans(string line){
		istringstream line_stream(line);
		string n;
		int counter = 0;
		while(line_stream >> n){							// For each input file line, obtain only LANs and skip the 1st item (bridge id)
			if(counter > 0){	// Skip bridge ID
				cout << "\tExamining n: " << n << endl;
				lans.push_back(n);
			}
			counter++;
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
		cout << "Sending from bridge"<< bridge_id << endl;
		cout << "Bridge's config:\n";
		config_message.print_config();
	}
	void Bridge::print_bridge(){
		cout << "Bridge #"<< bridge_id << endl;
		cout << "\tLANs:\n";
		for(int i = 0; i < lans.size(); i++){
			cout << "\t\t" << lans[i] << endl;
		}
		cout << "\tNeighbors:\n";
		for(int id: other_bridges){
			cout << "\t\t" << id << endl;
		}
		// for(int i = 0; i < other_bridges.size(); i++){
		// 	cout << "\t\t" << other_bridges[i].get_bridge_id() << endl;
		// }
		// auto it = other_bridges.cbegin();
		// while(it != other_bridges.cend()){
		// 	cout << "\t\t" << it.get_bridge_id() << endl;
		// 	++it;
		// }
	}
