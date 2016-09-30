#include "Config_Message.h"
Config_Message::Config_Message(){

}
Config_Message::Config_Message(int x, int y, int z){
	root = x;
	dist_root = y;
	sender = z;
}
bool Config_Message::is_better(Config_Message other){
	// cout << "Checking which message is better\n";
	if(root < other.get_root()){
		return true;
	}
	else if(root == other.get_root()){
		if(dist_root < other.get_dist_root()){
			return true;
		}
		else if(dist_root == other.get_dist_root()){
			if(sender < other.get_sender()){
				return true;
			}
		}
	}
	return false;
}
void Config_Message::print_config(){
	cout << "<"<< root<<","<< dist_root<<","<< sender<<">";
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
