#ifndef nato_h
#define nato_h

#include "natParser.h"

struct natOmi {
	
	natOmi(bool debug=false);

	bool natParseConfig(vector<NatConfig*>& out, vector<std::string>& configpath);
	bool natParseConfig(NatConfig& conf, string& configpath);

	std::vector<NatConfig*> conf;
	bool debug;
};

bool updateVars(NatConfig* conf);

#endif
