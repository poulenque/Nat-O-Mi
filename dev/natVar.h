#ifndef natVar_h
#define natVar_h

#include <yaml-cpp/yaml.h>

#include "natUnits.h"
#include "natColors.h"


struct NatVariable{

	NatVariable();
	NatVariable(const std::string& data, const std::string& var,const Unit& unit, const std::string& error);

	std::string data;
	std::string var;
	Unit unit;
	std::string error;
	size_t index;
	double value;
};

std::ostream& operator<<( std::ostream& out, const NatVariable& var);

typedef std::map<std::string, NatVariable*> MetaVar;

#endif
