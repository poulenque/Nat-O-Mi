#ifndef natArgs_h
#define natArgs_h

#include "natColors.h"

using namespace std;

typedef struct Args Args; 

struct Args{
	Args();
	string input_file_path;
	string output_file_path;
	string formula;
	vector<string> to_calculate_mean;
	vector<string> to_calculate_deviation;
	vector<string> to_calculate_gnuplot;
};

void process_args(int argc, char* argv[]);

Args get_args();

#endif
