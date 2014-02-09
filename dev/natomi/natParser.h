#ifndef natParser_h
#define natParser_h

#include "natYAML.h"

string natGetHeadings(const string& str, size_t& i, const char& c, const string& cc);
bool natParseHeader(NatConfig& config);

#endif
