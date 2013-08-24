#include <iostream>
#include <map> 
#include <algorithm>

#include "muParser.h"
#include "vector"
#include "string"
#include "natplot.cc"
#include "nattable.cc"

// Function string to double
int StrToDouble(std::string const& s)
{
    std::istringstream iss(s);
    double value;
    if (!(iss >> value)) throw std::runtime_error("invalid double in line");
    return value;
}
std::string DoubleToStr(double const& dbl)
{
	std::ostringstream strs;
	strs << dbl;
	return strs.str();
}
// Function callback
double MySqr(double a_fVal) 
{ 
  return a_fVal*a_fVal; 
}

double Assign(double a_fVal) 
{ 
  return a_fVal*a_fVal; 
}

// main program
int main(int argc, char* argv[])
{
//Parser will be deleted then merged
  using namespace mu;
  std::vector<std::string> data_line;
  for(unsigned int i=0;i < 3;i++)
	data_line.push_back(DoubleToStr(i+1));

  std::string formula = "result=U*I";

  std::map<unsigned,std::string> map_var; 
  map_var[0] = "U"; 
  map_var[1] = "I"; 
  map_var[2] = "R";

std::map<std::string,size_t>map_head;
  map_head["U"] = 0; 
  map_head["I"] = 1; 
  map_head["R"] = 2;

std::vector<std::string> a{"1","2","3"};
std::vector<std::string> b{"4","5","6"};
std::vector<std::string> c{"7","8","9"};


std::cout << textable_init(a,"This is a caption test","test");
std::cout << textable_content(b);
std::cout << textable_content(c);
std::cout << textable_end();
//std::cout << minimal_gnuplot_script("test",a, map_head) << std::endl;



  double result = 0.0;
//Mathematic parsing and evaluation
  try
  {
	std::vector<double> fVal;
	std::transform(data_line.begin(), data_line.end(),
		std::back_inserter(fVal), StrToDouble);

    Parser p;

	for(unsigned int i(0); i < fVal.size();i++)
        p.DefineVar(map_var[i], &fVal[i]); 


	p.DefineVar("result",&result);
    p.DefineFun("MySqr", MySqr);
//    p.DefineFun("=", Assign);
    p.SetExpr(formula);

    std::cout << p.Eval() << " result: " << result<< std::endl;
  }
  catch (Parser::exception_type &e)
  {
    std::cout << e.GetMsg() << std::endl;
  }
  return 0;
}
