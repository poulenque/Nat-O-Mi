#include <iostream>
#include <map> 
#include <algorithm>

#include <vector>
#include <string>
#include "natparser.h"
#include <ginac/ginac.h>


// Function string to double
double StrToDouble(std::string const& s);
std::string DoubleToStr(double const& dbl);

// main program
GiNaC::ex natConPute(const std::string& formula, std::vector<std::string>& line, std::map<std::string,size_t> dataName_str2num);

GiNaC::ex natDerive(const std::string& formula, const std::string& var, unsigned int nth);

GiNaC::ex natUncerError(const std::string& formula, const std::vector<NatInfo>& data_info, std::map<std::string,size_t> dataName_str2num);
