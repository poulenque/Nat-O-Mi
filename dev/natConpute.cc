#include "natConpute.h"


NatExpressions::NatExpressions(){}
NatExpressions::NatExpressions(const std::string& formula, size_t precision):prec(precision)
{
	//Parse the formula
	this->exp = this->reader(formula);
	//Get the symbol from the expression and write it down to a table
	this->table = this->reader.get_syms();
}


double NatExpressions::natConPute(MetaVar& vars)
{
    GiNaC::Digits = this->prec;
	GiNaC::ex eq = this->exp;
	double val;

	//Substitue each variable by its actual value from the line
	//=========================================================
	for(GiNaC::symtab::const_iterator it = this->table.begin();it != this->table.end(); ++it)
	{
		val = vars[it->first]->value;

		if(!std::isnan(val))
			eq = eq.subs(it->second == val);		
		//std::cout << eq << " =>" << eq.subs(it->second == val) << std::endl;
	}

	//Evaluating the equation and return the result if it's not Complex
	//=================================================================
	eq=eq.evalf();
	if(!GiNaC::ex_to<GiNaC::numeric>(eq).GiNaC::numeric::is_real())
	{
		std::cout 	
		<<CONSOL_RED_TEXT<< "The expressions "
		<<CONSOL_CYAN_TEXT<< this->exp
		<<CONSOL_RED_TEXT<< " contains Complex numbers!" 
		<<std::endl;
		return 0;
	}
	else
		return GiNaC::ex_to<GiNaC::numeric>(eq).GiNaC::numeric::to_double();	
}


GiNaC::ex natDerive(const std::string& formula, const std::string& var, unsigned int nth)
{

	GiNaC::parser reader;
	GiNaC::symtab table;
	GiNaC::ex e;

	e = reader(formula);
	table = reader.get_syms();
	
	//std::cout << "The derivative " << nth << "th of " << e << " with respect to " << var << " is: ";
	//std::cout << e.diff(GiNaC::ex_to<GiNaC::symbol>(table[var]), nth) << "." << std::endl;

	table.clear();
	return e.diff(GiNaC::ex_to<GiNaC::symbol>(table[var]), nth);
}

std::string NatExpressions::natUncerError(MetaVar& vars)
{
	GiNaC::ex eq = this->exp;
	GiNaC::ex sum; //empty exp to concatenate the expression for uncertainties formula			

	for(GiNaC::symtab::const_iterator it = this->table.begin();it != this->table.end(); ++it)
		sum += pow(eq.diff(GiNaC::ex_to<GiNaC::symbol>(it->second))*GiNaC::symbol(vars[it->first]->error),2);

		//TODO CHECK WITH ANOTHER software
	//Put the value of the equation to the resultvar error /\ error value
	//===================================================================
	std::ostringstream s;
	s << sqrt(sum);
	return s.str();
}
