
#include "consol_color.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

#include "natomi.h"
#include "arguments.h"

#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include <ginac/ginac.h>

#define NATOMI_VERSION 0.31

double MySqr(double a_fVal) { 
	return a_fVal*a_fVal; 
}


#define NATOMI_TEMP_EXIT_FUNCTION(TRUC) \
	if(TRUC){\
		input_file.close();\
		output_file.close();\
		exit(1);\
	}

using namespace std;

int main(int argc, char* argv[]) {
	boost::program_options::options_description desc("Options");
	vector<string> input;
	desc.add_options()
		("help,h"   , "produce help message")
		("input,i"  ,  boost::program_options::value< vector<string> >(&input), "input file")
		("version,v", "show version")
	;

	boost::program_options::variables_map vm;
	// try{
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
	// }catch(e){
	// 	cout<<"prout"<<endl;
	// }
	boost::program_options::notify(vm);

	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}
	if (vm.count("version")) {
		cout << NATOMI_VERSION << "\n";
		return 1;
	}

	// if (vm.count("compression")) {
	// 	cout << "Compression level was set to " 
	// 	<< vm["compression"].as<int>() << ".\n";
	// } else {
	// 	cout << "Compression level was not set.\n";
	// }




	natinit();




	return 0;




	natinit();
	//====================================================
	//traiter les arguments
	process_args(argc,argv);
	//====================================================


	//GiNaC::Digits = 1.0; //Defines the number of digits ofr GiNaC expressions
	string read_line;
	vector<string> data_line;
	vector<NatInfo> data_info;
	map<string, size_t> 	dataName_str2num;


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
	NATOMI_TEMP_EXIT_FUNCTION(exiting)

	//trouver la ligne avec les noms de variable
	if(!natParseNext(input_file,data_line)){
		cout<<CONSOL_RED_TEXT<<"\""<<CONSOL_CYAN_TEXT<<get_args().input_file_path
		<<CONSOL_RED_TEXT<<"\" is empty."<<endl;
		exiting=true;
	}
	NATOMI_TEMP_EXIT_FUNCTION(exiting)

	data_info=natParseHeader(data_line);

	//str2num
	for(size_t i=0;i<data_info.size();i++)
		dataName_str2num.insert(std::pair<string,size_t>(data_info[i].name,i) );
	



	//TODO
	//Init of data_line computing
	
	//Here is the error init computation
	//natDerive("U*I_", "U", 2);
	size_t nheader(data_info.size());
	for(size_t i(0); i < nheader; i++)
	{	
		if(data_info[i].error == "*")
		{
			data_info[i].error = data_info[i].name+"_error";
			NatInfo new_column;
			new_column.error = ".";
			new_column.unit = data_info[i].unit;
			new_column.formula = boost::lexical_cast<std::string>(natUncerError(data_info[i].formula,data_info,dataName_str2num));
			new_column.name = data_info[i].error;
			data_info.push_back(new_column);
			data_line.push_back(new_column.name+"[UNIT GLA]"+"["+new_column.formula+"]");
		}	
	}

	//This doesnt write the corret header!!!! problem
	output_file << data_line << std::endl;

	while(natParseNext(input_file,data_line) && input_file.good())
	{

		if(data_line.size() != nheader)// check if there is no blanks from the original header size
		{
			std::cout 	<< CONSOL_RED_TEXT  << "The line "
						<< CONSOL_CYAN_TEXT <<"xxx"
						<<CONSOL_RED_TEXT <<" has incorrect number of columns" 
						<< std::endl;
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
		for(unsigned int i(0); i < data_info.size(); i++)
		{	
			if(!data_info[i].formula.empty())
			{
				GiNaC::ex result(natConPute(data_info[i].formula,data_line,dataName_str2num));

				//Keep the sme amount of column but computing the good values
				if (GiNaC::is_a<GiNaC::numeric>(result) && i < nheader)
					data_line[i] = double2str(GiNaC::ex_to<GiNaC::numeric>(result).to_double()); //STUPID ????

				//Append the column
				else if(i >= nheader)
					data_line.push_back(double2str(GiNaC::ex_to<GiNaC::numeric>(result).to_double())); //STUPID ????
			}
		}

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
	return 0;
}





