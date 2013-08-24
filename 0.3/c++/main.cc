#include <iostream>
#include <muParser.h>
#include <vector>
#include <string>
#include <map>
#include <fstream>


#include "arguments.h"
#include "natparser.h"

string double2str(double x) {
	std::ostringstream oss;
	oss << x;
	return oss.str();
}

double MySqr(double a_fVal) { 
	return a_fVal*a_fVal; 
}

int main(int argc, char* argv[]) {
	using namespace std;

	string read_line;
	vector<string> data_line;
	vector<string> data_name_num_to_str;
	map<string, unsigned int> data_name_str_to_num;


	//====================================================
	//traiter les arguments
	process_args(argc,argv);
	//====================================================
	//lire le fichier, extraire les donnees
	bool exiting=false;
	
	ofstream output_file(get_args().output_file_path);
	if(!output_file.is_open()){
		cout<<"could not open file"<<get_args().output_file_path<< endl;
		exiting=true;
	}
	ifstream input_file(get_args().input_file_path);
	if(!input_file.is_open()){
		cout<<"coult not open file"<<get_args().input_file_path<<endl;
		exiting=true;
	}
	if(exiting)exit(0);



	//loop1
	//trouver la ligne avec les noms de vaiable
	while(input_file.good()){
		getline(input_file,read_line);
		data_line = natparse(read_line);
	}

	//loop2
	//lire data
	//mettre en forme
	//fairee les calculs
	//ecrire dans output

	input_file.close();
	output_file.close();
	//====================================================


	using namespace mu;

	try{
		double fVal = 1;
		Parser p;
		p.DefineVar("a", &fVal); 
		p.DefineFun("pouet", MySqr); 
		p.SetExpr("pouet(a)*_pi+min(10,a)");

		for (std::size_t a=0; a<10; ++a){
			fVal = a;  // Change value of variable a
			std::cout << p.Eval() << std::endl;
		}
	}
	catch (Parser::exception_type &e){
		std::cout << e.GetMsg() << std::endl;
	}

	return 0;
}






