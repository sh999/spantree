#include <iostream>
using namespace std;
struct s{
	int x;
	int y;
	s(){

	}	
	s(int a, int b){
		x = a;
		x = b;
	}
};
int main(){
	// s bla(3,2);
	s bla;
	bla = s(3,2);
	cout << bla.x << " " << bla.y << endl;
}