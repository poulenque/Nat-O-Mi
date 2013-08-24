#include "natparser.h"

#include <iostream>
#include <string>
#include <sstream>

vector<string> natparse(string read_line){

	vector<string> v;




	string myText("some 	text   to		 tokenize");
	istringstream iss(myText);
	string token;
	while(getline(iss, token, ' ')) {
		cout << token << endl;
	}
	cout<<"====================="<<endl;



	//v.push_back(strtok(read_line.c_str," ,.-\t"));	
	return v;
}








input :
"vat_1[][] 		vat_2[] []  	  var_3[] []"
"1  		    41 	 	 			58 "
"2  		    415 	 	 			558 "
"41  		    415 	 	 			584 "
"2  		    451 	 	 			528 "

output :
{
"var_1[][]"
"var_2[][]"
"var_3[][]" }