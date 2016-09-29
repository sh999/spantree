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
void Config_Message::set_root(int x){
	root = x;
}
void Config_Message::set_dist_root(int x){
	dist_root = x;
}
void Config_Message::set_sender(int x){
	sender = x;
}
int Config_Message::get_root(){
	return root;
}
int Config_Message::get_dist_root(){
	return dist_root;
}
int Config_Message::get_sender(){
	return sender;
}
