#ifndef natVar_h
#define natVar_h

#include "natUnits.h"
#include "natColors.h"

struct NatVariable{

	NatVariable();
	NatVariable(const std::string& data, const std::string& var,const Unit& unit, const std::string& error,size_t index=UNINDEXED,const double value=0.0);
	NatVariable(NatVariable& nat);

	~NatVariable();

	std::string data;
	std::string var;
	Unit unit;
	std::string error;
	long long int index;
	double value;
};

std::ostream& operator<<( std::ostream& out, const NatVariable& var);

typedef std::unordered_map<std::string, NatVariable*> MetaVar;

#endif
