#ifndef NAT_UTILS_H
#define NAT_UTILS_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

ostream & operator<<(ostream& out,vector<string> v);
string double2str(double const x);
double str2double( const string s );

#endif
