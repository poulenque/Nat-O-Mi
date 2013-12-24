#include <string>
#include <iostream>
using namespace std;
int main(){
	string str;
	for(unsigned int i=0;i<2000;i++){
		str+="10";
		cout<<sizeof(str)<<endl;
	}
}
