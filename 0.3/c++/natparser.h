#ifndef NATPARSE_H
#define NATPARSE_H

#include <vector>
#include <string>
#include <fstream>
#include "natunits.h"

using namespace std;

typedef struct natHeader natHeader;

struct natInfo{
	string name;
	Unit unit;
	string error;
	string formula;
};

vector<string> natParseStr(string read_line);
vector<string> natParseNext(ifstream& input_file);
vector<natInfo> natParseHeader(vector<string> input);

#endif