#include <iostream>
#include <map> 
#include <algorithm>

#include "muParser.h"
#include "vector"
#include "string"


// Function string to double
int StrToDouble(std::string const& s);
std::string DoubleToStr(double const& dbl);

//CALLBACK function
double Assign(double assigned, double value);

// main program
void natomi_core(std::string formula, std::vector<std::string> head, std::vector<double>& line);

