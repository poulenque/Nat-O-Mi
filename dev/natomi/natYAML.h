#ifndef natYAML_h
#define natYAML_h

#include <yaml-cpp/yaml.h>
#include "natConfig.h"

bool operator>>(const YAML::Node& node, NatConfig& config);
bool operator>>(const YAML::Node& node, NatData& datas);
bool operator>>(const YAML::Node& node, MetaExpr& exprs);
bool operator>>(const YAML::Node& node, MetaVar& vars);
bool operator>>(const YAML::Node& node, std::vector<NatOutPute>& vars);

#endif
