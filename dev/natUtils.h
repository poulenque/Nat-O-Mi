#ifndef natUtils_h
#define natUtils_h

#include <string>
#include <iostream>
#include <vector>
#include <boost/lexical_cast.hpp> //TODO usefull for string to double


std::ostream & operator<<(std::ostream& out,std::vector<std::string> v);
std::string double2str(double const x);
double str2double( const std::string s );

double StrToDouble(std::string const& s);

#endif
