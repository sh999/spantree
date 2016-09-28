#include "Bridge.h"

	Bridge::Bridge(string line){
		bridge_id = int(line[0]);	// Numeric ID of bridge
		config_message = Config_Message(get_bridge_id(), 0, get_bridge_id());   // Default config message <ID, 0, ID>
		// cout <<  "Line is:x"<< line "x" << endl;
		connect_bridge_with_lans(line);
	}
	void Bridge::connect_bridge_with_lans(string line){
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
	}
