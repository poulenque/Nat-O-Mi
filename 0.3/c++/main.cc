#include <iostream>
#include <muParser.h>
#include <vector>
#include <string>
#include <map>
#include <fstream>


#include "arguments.h"
#include "natparser.h"

ostream & operator<<(ostream& out,vector<string> v){
	for (const auto& t : v)
		out<<t<<" ";
	return out;
}

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
	vector<natInfo> data_info;
	vector<string> 				data_name_num_to_str;
	map<string, size_t> 	data_name_str_to_num;


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



	//trouver la ligne avec les noms de vaiable
	data_line=natParseNext(input_file);
	if(data_line.size()==0){
		cout<<get_args().input_file_path<<" is empty."<<endl;
		exit(0);
	}

	data_info=natParseHeader(data_line);

	//test
	data_name_num_to_str=data_line;


	//create the map
	for(size_t i=0;i<data_name_num_to_str.size();i++)
		data_name_str_to_num.insert(std::pair<string,size_t>(data_name_num_to_str[i],i) );
	








	//loop
	//lire data
	//mettre en forme
	//fairee les calculs
	//ecrire dans output

	while(data_line.size()==0 && input_file.good()){

	}




	input_file.close();
	output_file.close();
	//====================================================


	using namespace mu;

	// try{
	// 	double fVal = 1;
	// 	double fValb = 1;
	// 	Parser p;
	// 	p.DefineVar("a", &fVal); 
	// 	p.DefineVar("b", &fValb); 
	// 	p.DefineFun("pouet", MySqr); 
	// 	p.SetExpr("b = pouet(a)*_pi+min(10,a)");

	// 	for (std::size_t a=0; a<10; ++a){
	// 		fVal = a;  // Change value of variable a
	// 		fValb = a;
	// 		std::cout << p.Eval() << " " << fValb<< std::endl;
	// 	}
	// }
	// catch (Parser::exception_type &e){
	// 	std::cout << e.GetMsg() << std::endl;
	// }
	
	return 0;
}






