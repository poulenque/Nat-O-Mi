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
GiNaC::ex natDerive(const std::string& formula, const std::string& var, unsigned int nth);
