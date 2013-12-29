#ifndef MAIN_CC
#define MAIN_CC

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <ginac/ginac.h>

#include "natColors.h"
#include "natConpute.h"
#include "natTest.h"

#define NATOMI_VERSION 0.31

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
	try{
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
	}catch(boost::program_options::error& e){
		//cout<<"prout"<<endl;
	}
	boost::program_options::notify(vm);

	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}
	if (vm.count("version")) {
		cout << NATOMI_VERSION << "\n";
		return 1;
	}
	if (!vm.count("input")) {
		cout << CONSOL_RED_TEXT << "-i input file path is missing ! go fuck yourself !\n" <<CONSOL_NORMAL_TEXT;
		return 1;
	}


	vector<NatConfig> test;
	if(!natParseConfig(test,input))
		exit(1);//Leave the buggy program!

	test_Parser(test);
	test_Working(test);


	return 0;
}
#endif
