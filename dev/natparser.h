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
	std::string expr;
	size_t index;
};

typedef std::map<std::string, NatVariable*> MetaName;

typedef std::map<std::string, std::ifstream*> NatData;

typedef std::map<std::string,std::string> NatTrouDuc;

struct NatOutPute{

	std::vector<std::string> contents;
	std::string path;
};

struct NatConfig{

	NatConfig();

	NatTrouDuc traduc;
	MetaName natvar;
	NatData datas;
	

	void updateVars();

	std::vector<NatOutPute> text;
	std::vector<NatOutPute> latex;
	std::vector<NatOutPute> gnuplot;
};


bool natParseNext(std::ifstream* input_file,std::vector<std::string>& output);
bool NatParseNextLines(NatOutPute& output);
std::vector<double> natParseContent(std::vector<std::string> input);

//NatOutPute NatParseConfig(std::string path);
bool natParseConfig(NatConfig& conf , std::string configpath);
bool natParseConfig(std::vector<NatConfig>& out,std::vector<std::string> configpath);

bool natParseHeader(NatConfig& config);
MetaName natParseHeader(std::vector<std::string> input);

bool operator>>(const YAML::Node& node, NatData& datas);
bool operator>>(const YAML::Node& node, MetaName& vars);
bool operator>>(const YAML::Node& node, std::vector<NatOutPute>& vars);
bool operator>>(const YAML::Node& node, NatConfig& config);

std::ostream& operator<<( std::ostream& out, const NatVariable& var);

MetaName::const_iterator findPrefix(const MetaName& map, const std::string& search_for);

#endif
