#include <iostream>
#include <map> 
#include <algorithm>

#include "vector"
#include "string"
#include "natparser.h"
#include <ginac/ginac.h>


// Function string to double
double StrToDouble(std::string const& s);
std::string DoubleToStr(double const& dbl);

// main program
void natConPute(const std::vector<natInfo>& data_info, std::vector<std::string>& line, map<std::string,size_t> dataName_str2num);

void natDerive(const std::vector<natInfo>& data_info, std::vector<std::string>& line, map<std::string,size_t> dataName_str2num);
