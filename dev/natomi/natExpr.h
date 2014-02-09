#ifndef natExpr_h
#define natExpr_h

#include <ginac/ginac.h>
#include "natData.h"

struct NatExpressions{

	NatExpressions();
	NatExpressions(const std::string& formula, size_t precision=NatExprPrec);

	double natConPute(MetaVar& vars);
	std::string natUncerError(MetaVar& vars);

	//Define the parser, symbol table and expression to evaluate
	GiNaC::parser reader;
	GiNaC::symtab table;
	GiNaC::ex exp;
	size_t prec;
};

typedef std::unordered_map<std::string, NatExpressions*> MetaExpr;

// main program
GiNaC::ex natDerive(const std::string& formula, const std::string& var, unsigned int nth);
#endif
