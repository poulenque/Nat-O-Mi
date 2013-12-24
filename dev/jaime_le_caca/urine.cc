#include <map>
#include <iostream>

using namespace std;

struct vomi{
	int crotte;
};

static map<string,vomi*> perfect;

int main(){
	map<string, int*> prout;
	int caca;
	prout.insert(pair<string,int*>("pipi",&caca));
	cout<<prout["pipi"]<<endl;
	
	map<string, vomi*> etron;
	vomi diharee;
	etron.insert(pair<string,vomi*>("pipi",&diharee));
	cout<<etron["pipi"]<<endl;

	perfect.insert(pair<string,vomi*>("pipi",&diharee));
	cout<<perfect["pipi"]<<endl;

	return 0;
}
