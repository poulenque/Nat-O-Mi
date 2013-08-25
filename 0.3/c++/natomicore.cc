#include <iostream>
#include "natomicore.h"
#include <muParser.h>
using namespace mu;

// Function string to double
int StrToDouble(std::string const& s)
{
    std::istringstream iss(s);
    double value;
    if (!(iss >> value)) throw std::runtime_error("invalid double in line");
    return value;
}

//Callback function
double Assign(double assigned, double value)
{ 
	return assigned=value; 
}

void natomi_core(std::string formula,  std::vector<std::string> head, std::vector<double>& line)
{
  try
  {
    Parser p;
	p.DefineFun("Assign",Assign);
    p.SetExpr("Assign("+formula+")");

	for(unsigned int i(0); i < line.size();i++)
	    p.DefineVar(head[i], &line[i]); 

    std::cout << p.Eval() << std::endl;
  }
  catch (Parser::exception_type &e)
  {
    std::cout << e.GetMsg() << std::endl;
  }
}
