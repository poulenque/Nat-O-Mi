#ifndef natUtils_h
#define natUtils_h

#include "natOmi.h"

std::ostream & operator<<(std::ostream& out,std::vector<std::string> v);
std::string double2str(double const x);
double str2double( const std::string s );

double StrToDouble(std::string const& s);

//TODO TEMPLATE
//MetaName::const_iterator findPrefix(const MetaName& map, const std::string& search_for);

#endif
