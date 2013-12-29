#ifndef natConpute_h
#define natConpute_h

#include <ginac/ginac.h>

#include "natParser.h"


// Function string to double
double StrToDouble(std::string const& s);
std::string DoubleToStr(double const& dbl);

// main program
GiNaC::ex natDerive(const std::string& formula, const std::string& var, unsigned int nth);
#endif
