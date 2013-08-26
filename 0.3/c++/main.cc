#include "consol_color.h"
#include <iostream>
#include <muParser.h>
#include <vector>
#include <string>
#include <map>
#include <fstream>

#include "natUtils.h"
#include "arguments.h"
#include "natparser.h"




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
	vector<string> 				dataName_num2str;//might be useless
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

	//num2str str2num
	dataName_num2str=data_line;
	for(size_t i=0;i<dataName_num2str.size();i++)
		dataName_str2num.insert(std::pair<string,size_t>(dataName_num2str[i],i) );
	







	while(data_line.size()==0 && input_file.good()){
		//lire data
		data_line=natParseNext(input_file);
		
		//TODO
		//==========================================================
		//==========================================================
		//==========================================================
		//mettre en forme
		//faire les calculs sur la ligne
		vector<double> parsed = natParseContent(data_line);

		//TODO
		//calcules pour la colonne


		//TODO
		//ecrire dans output proprement
		for(size_t i=0;i<parsed.size();i++){
			output_file<<parsed[i]<<" ";
		}output_file<<endl;
		//==========================================================
		//==========================================================
		//==========================================================

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






