#ifndef NATPARSE_H
#define NATPARSE_H

#include <vector>
#include <string>
#include <fstream>
#include "natunits.h"


typedef struct natHeader natHeader;

struct natInfo{
	natInfo();
	std::string name;
	Unit unit;
	std::string error;
	double error_value;
	std::string formula;
};

bool natParseNext(std::ifstream& input_file,std::vector<std::string>& output);
std::vector<natInfo> natParseHeader(std::vector<std::string> input);
std::vector<double> natParseContent(std::vector<std::string> input);

#endif
