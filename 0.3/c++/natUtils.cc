#include "natUtils.h"

#include <sstream>

ostream & operator<<(ostream& out,vector<string> v){
	for (const auto& t : v)
		out<<t<<" ";
	return out;
}

string double2str(double const x) {
	std::ostringstream oss;
	oss << x;
	return oss.str();
}

double str2double( const string s ) {
	std::istringstream i(s);
	double x;
	if (!(i >> x))
		return 0;
	return x;
} 
