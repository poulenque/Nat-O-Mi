#ifndef NATPARSE_H
#define NATPARSE_H

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "natunits.h"
#include <yaml-cpp/yaml.h>
#include <ginac/ginac.h>
#include "natUtils.h"

struct NatLateXt{

	std::string path;
	std::vector<std::string> contents;
};

struct NatData{

	NatData();
	std::string name;
	std::ifstream * file;
	std::vector<std::string> readline;
	std::vector<std::string> header_name;
	std::vector<std::string> header_unit;
	std::vector<std::string> header_error;
	void update();
};

struct NatVariable{

	NatVariable();
	std::string name;
	NatData * data;
	size_t dataIndex;
	Unit unit;
	double value;
	std::string value_str;
};

struct NatExpression{

	NatExpression();
	std::string name;
	//NatData * data;
	Unit unit;
	double value;
	//std::string value_str;
};

struct NatConfig{

	NatConfig();
	void update();
	std::vector<NatData> datas;
	std::vector<NatVariable> variables;
	GiNaC::symtab variables_; 
	std::vector<NatExpression> expressions;
	std::vector<NatLateXt> text;
	std::vector<NatLateXt> latex;
	std::vector<NatLateXt> gnuplot;
};

struct NatInfo{

	NatInfo();
	//will be written
	std::string name;
	Unit unit;
	std::string error;
	double error_value;
	std::string formula;
};

struct NatOutPute{

	std::vector<NatInfo> content;
	std::map<std::string,std::ifstream> sources;
};

bool natParseNext(std::ifstream& input_file,std::vector<std::string>& output);
std::vector<NatInfo> natParseHeader(std::vector<std::string> input);
std::vector<double> natParseContent(std::vector<std::string> input);
// NatOutPute NatParseConfig(std::string path);
bool NatParseNextLines(NatOutPute& output);

bool natParseConfig(NatConfig& conf , std::string configpath);
bool natParseConfig(std::vector<NatConfig>& out,std::vector<std::string> configpath);



bool operator>>(const YAML::Node& node, std::vector<NatData>& datas);
bool operator>>(const YAML::Node& node, std::vector<NatVariable>& vars);
bool operator>>(const YAML::Node& node, std::vector<NatExpression>& vars);
bool operator>>(const YAML::Node& node, std::vector<NatLateXt>& vars);
bool operator>>(const YAML::Node& node, NatConfig& config);

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



//Main function
// GiNaC::ex natConPute(
// 	std::vector<NatExpression> natExpTab,
// 	GiNaC::symtab& natSymTab,
// 	std::vector<std::string>& line,
// 	std::map<std::string,size_t> dataName_str2num)
// {
// 	//On reassigne les valeurs des lignes aux nouvelles varaibles
// 	for(GiNaC::symtab::iterator it = natSymTab.begin();it != natSymTab.end(); ++it)
// 	{
// 		size_t id(dataName_str2num[it->first]);
// 		if(!std::isnan(StrToDouble(line[id])))
// 			it->second = GiNaC::ex(StrToDouble(line[id]));
// 	}
// 	for(unsigned int i(0); i < natExpTab.size(); i++)
// 		natExpTab[i].eval();
// }
