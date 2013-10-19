
#include <string>

using namespace std;

union prout{
	prout(){}
	~prout(){}
	double caca;
	string pipi;
};

int main(){
	union prout crotte;
	string vomi ("diharee");
	crotte.pipi = vomi;
	union prout pisse = crotte;
	return 0;
}

