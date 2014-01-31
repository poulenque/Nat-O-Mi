#ifndef natParser_h
#define natParser_h

#include <yaml-cpp/yaml.h>

#include "natUnits.h"
#include "natColors.h"
#include "natYAML.h"


bool natParseConfig(NatConfig& conf, std::string configpath);
bool natParseNext(std::ifstream* input_file,std::vector<std::string>& output);
bool NatParseNextLines(NatOutPute& output);
std::vector<double> natParseContent(std::vector<std::string> input);
//NatOutPute NatParseConfig(std::string path);
bool natParseConfig(std::vector<NatConfig*>& out,std::vector<std::string> configpath);
bool natParseHeader(NatConfig& config);
MetaVar natParseHeader(std::vector<std::string> input);

#endif
