#ifndef main_cc
#define main_cc

#include "natTest.h"
#include "../csympy/csympy.h"
//#include "test.cc"

int main(int argc, char* argv[])
{
	bool debug(false);
	vector<string> input;

	boost::program_options::options_description desc("Options");
	desc.add_options()
		("help,h"   , "produce help message")
		("input,i"  ,  boost::program_options::value< vector<string> >(&input), "input file")
		("version,v", "show version")
		("debug,d", "print debug");

	boost::program_options::variables_map vm;
	try{
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
	}catch(boost::program_options::error& e){
		cout << CONSOL_RED_TEXT << SOFT_NAME << SOFT_VERSION << "option Error!" <<endl;
		cout << CONSOL_RED_TEXT << e.what() << CONSOL_NORMAL_TEXT <<endl;
		exit(EXIT_FAILURE);
	}
	boost::program_options::notify(vm);

	if (vm.count("help")) {
		cout << desc << "\n";
		exit(EXIT_SUCCESS);
	}
	if (vm.count("version")) {
		cout << SOFT_VERSION << "\n";
		exit(EXIT_SUCCESS);
	}
	if (vm.count("debug"))
		debug=true;

	if (!vm.count("input")) {
		cout << CONSOL_RED_TEXT << "-i input file path is missing!" << CONSOL_NORMAL_TEXT << endl;
		exit(EXIT_FAILURE);
	}


	natOmi test(debug);
	if(!test.natParseConfig(test.conf,input))
		exit(EXIT_FAILURE);

	test_Parser(test);
	test_Working(test);

   /* test_sin();
    test_cos();
    test_f();*/



	return 0;
}
#endif
