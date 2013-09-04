#ifndef NAT_UTILS_H
#define NAT_UTILS_H

#include <string>
#include <iostream>
#include <vector>


std::ostream & operator<<(std::ostream& out,std::vector<std::string> v);
std::string double2str(double const x);
double str2double( const std::string s );

#endif
