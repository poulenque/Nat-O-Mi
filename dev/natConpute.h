#ifndef natConpute_h
#define natConpute_h

#include <ginac/ginac.h>
#include "natVar.h"

#define NatExprPrec 50
#define NatErrorSuffix "_error"

typedef std::map<std::string, std::ifstream*> NatData;

struct NatExpressions{

	NatExpressions();
	NatExpressions(const std::string& formula, size_t precision=NatExprPrec);

	double natConPute(MetaVar& vars);
	std::string natUncerError(MetaVar& vars);

	//Define the parser, symbol table and exypression to evaluate
	GiNaC::parser reader;
	GiNaC::symtab table;
	GiNaC::ex exp;
	size_t prec;
};

typedef std::map<std::string, NatExpressions*> MetaExpr;

// Function string to double
double StrToDouble(std::string const& s);
std::string DoubleToStr(double const& dbl);

// main program
GiNaC::ex natDerive(const std::string& formula, const std::string& var, unsigned int nth);
#endif
