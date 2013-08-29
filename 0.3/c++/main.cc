#include "consol_color.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

#include "natUtils.h"
#include "arguments.h"
#include "natparser.h"
#include "natconpute.h"




double MySqr(double a_fVal) { 
	return a_fVal*a_fVal; 
}


#define TEMP_EXIT_FUNCTION \
		input_file.close();\
		output_file.close();\
		exit(0);


int main(int argc, char* argv[]) {
	using namespace std;

	string read_line;
	vector<string> data_line;
	vector<natInfo> data_info;
	map<string, size_t> 	dataName_str2num;


	//====================================================
	//traiter les arguments
	process_args(argc,argv);
	//====================================================
	//lire le fichier, extraire les donnees
	bool exiting=false;
	
	ofstream output_file(get_args().output_file_path);
	if(!output_file.is_open()){
		cout<<CONSOL_RED_TEXT<<"could not open file"<<CONSOL_CYAN_TEXT<<get_args().output_file_path<< endl;
		exiting=true;
	}
	ifstream input_file(get_args().input_file_path);
	if(!input_file.is_open()){
		cout<<CONSOL_RED_TEXT<<"could not open file"<<CONSOL_CYAN_TEXT<<get_args().input_file_path<<endl;
		exiting=true;
	}
	if(exiting){
		TEMP_EXIT_FUNCTION
	}

	//trouver la ligne avec les noms de variable
	data_line=natParseNext(input_file);
	if(data_line.size()==0){
		cout<<CONSOL_RED_TEXT<<"\""<<CONSOL_CYAN_TEXT<<get_args().input_file_path
		<<CONSOL_RED_TEXT<<"\" is empty."<<endl;
		TEMP_EXIT_FUNCTION
	}

	data_info=natParseHeader(data_line);

	//str2num
	for(size_t i=0;i<data_info.size();i++)
		dataName_str2num.insert(std::pair<string,size_t>(data_info[i].name,i) );
	



	//Write the first line of the input file into the output file, which is the header
	output_file << data_line << std::endl;

	while(data_line.size()!=0 && input_file.good()){
		//lire data
		if(data_line.size()!=0)
			data_line=natParseNext(input_file);

		if(data_line.size() != data_info.size()){
			std::cout<< CONSOL_RED_TEXT << "The line "<< CONSOL_CYAN_TEXT <<"xxx"<<CONSOL_RED_TEXT <<" has incorrect number of columns" << std::endl;
			exit(1);
		}

		//TODO
		//==========================================================
		//==========================================================
		//==========================================================
		//mettre en forme
		//faire les calculs sur la ligne
		//vector<double> parsed = natParseContent(data_line);

		//TODO
		//calcules pour la colonne
		natConPute(data_info, data_line, dataName_str2num);

		//TODO
		//calcules pour les incertitudes
		//natDerive(data_info, data_line, dataName_str2num);

		//TODO
		//ecrire dans output proprement
		output_file << data_line << std::endl;
		//==========================================================
		//==========================================================
		//==========================================================

	}
	
	input_file.close();
	output_file.close();
	//====================================================



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






