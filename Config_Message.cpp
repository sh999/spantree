#include "Config_Message.h"
Config_Message::Config_Message(){

}
Config_Message::Config_Message(int x, int y, int z){
	root = x;
	dist_root = y;
	sender = z;
}
void Config_Message::print_config(){
	cout << "<"<< root<<","<< dist_root<<","<< sender<<">" << endl;
}

