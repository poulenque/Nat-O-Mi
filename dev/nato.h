#ifndef nato_h
#define nato_h

#include "natParser.h"


struct natOmi {
	
	natOmi(){};

	std::vector<NatConfig*> conf;
};

bool updateVars(NatConfig* conf);//Useless to put in natOmi ?? TODO

#endif
