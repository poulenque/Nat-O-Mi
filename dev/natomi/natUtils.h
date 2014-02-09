#ifndef natUtils_h
#define natUtils_h

#include "includes.h"

std::ostream & operator<<(std::ostream& out,std::vector<std::string> v);
std::string DoubleToStr(double const x);
double StrToDouble(std::string const& s);
void skipBlanks(const string& str, size_t& pointer);

#endif
