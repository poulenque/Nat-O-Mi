#ifndef NATPARSE_H
#define NATPARSE_H

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "natunits.h"



struct NatInfo{
	NatInfo();
	//will be written
	std::string name;
	Unit unit;
	std::string error;
	double error_value;
	std::string formula;
};

bool natParseNext(std::ifstream& input_file,std::vector<std::string>& output);
std::vector<NatInfo> natParseHeader(std::vector<std::string> input);
std::vector<double> natParseContent(std::vector<std::string> input);

struct NatOutPute{
	std::vector<NatInfo> content;
	std::map<std::string,std::ifstream> sources;
};

NatOutPute NatParseConfig(std::string path);
bool NatParseNextLines(NatOutPute& output);

#endif




//usage :
// 
// output = NatParseConfig("/home/doek/config")
//  -> will get all column with formulae and unid
//  -> have to find all needed variables
// 
// write header
//
// while(NatParseNextLines(output))
//   calculateValues

