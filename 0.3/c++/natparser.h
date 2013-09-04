#ifndef NATPARSE_H
#define NATPARSE_H

#include <vector>
#include <string>
#include <fstream>
#include "natunits.h"

using namespace std;

typedef struct natHeader natHeader;

struct natInfo{
	natInfo();
	string name;
	Unit unit;
	string error;
	double error_value;
	string formula;
};

vector<string> natParseNext(ifstream& input_file);
vector<natInfo> natParseHeader(vector<string> input);
vector<double> natParseContent(vector<string> input);

#endif
