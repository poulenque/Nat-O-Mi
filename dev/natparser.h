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

struct NatVariable{

	NatVariable();
	std::string name;
	Unit unit;
	std::string error;
	double error_value;
	std::string expr;
};

typedef std::map<std::string, NatVariable*> MetaName;

struct NatData{

	NatData();
	std::string name;
	std::ifstream* file;
	std::vector<NatVariable> variables;
	void update();
};

struct NatOutPute{

	std::vector<std::string> contents;
	std::string path;
};

struct NatConfig{

	NatConfig();
	void update();

	GiNaC::symtab variables_;
	MetaName natvar;

	std::vector<NatData> datas;
	std::vector<NatOutPute> text;
	std::vector<NatOutPute> latex;
	std::vector<NatOutPute> gnuplot;
};


bool natParseNext(std::ifstream* input_file,std::vector<std::string>& output);
bool NatParseNextLines(NatOutPute& output);
std::vector<double> natParseContent(std::vector<std::string> input);

// NatOutPute NatParseConfig(std::string path);
bool natParseConfig(NatConfig& conf , std::string configpath);
bool natParseConfig(std::vector<NatConfig>& out,std::vector<std::string> configpath);

bool natParseHeader(NatConfig& config);
MetaName natParseHeader(std::vector<std::string> input);

bool operator>>(const YAML::Node& node, std::vector<NatData>& datas);
bool operator>>(const YAML::Node& node, MetaName& vars);
bool operator>>(const YAML::Node& node, std::vector<NatOutPute>& vars);
bool operator>>(const YAML::Node& node, NatConfig& config);

#endif
