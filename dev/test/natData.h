#ifndef natData_h
#define natData_h

#include "natVar.h"

struct Data{

	Data();
	Data(const string& f);
	~Data();

	bool updateVars();

	const string path;
	string buffer;
	size_t pointer;
	std::unordered_map<long long int, NatVariable*> vars;

};

typedef std::unordered_map<std::string, Data> NatData;

#endif
