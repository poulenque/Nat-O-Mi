#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>
#include <vector>

#define Nat_O_Mi_VERSION__ "0.3"

using namespace std;

typedef struct Args Args; 

struct Args{
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