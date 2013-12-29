#include <iostream>
#include "natconpute.h"
#include "natUtils.h"
#include <boost/lexical_cast.hpp>

// Function string to double
double StrToDouble(std::string const& s)
{
	double value;
    try {
        value = boost::lexical_cast<double>(s);
    } catch (boost::bad_lexical_cast const& e){
		value = std::numeric_limits<double>::quiet_NaN();
    }
	return value;
}

//Main function
double NatExpressions::natConPute(NatTrouDuc& traduc, MetaName& vars)
{
    GiNaC::Digits = 5; //TODO ask for precision after dot
	GiNaC::ex eq = this->exp;
	std::string val;

	//Substitue each variable by its actual value from the line
	//=========================================================
	for(GiNaC::symtab::const_iterator it = this->table.begin();it != this->table.end(); ++it)
	{
		val = vars[traduc[it->first]]->value;

		if(!std::isnan(StrToDouble(val)))
			eq = eq.subs(it->second == StrToDouble(val));		
		//std::cout << eq << " =>" << eq.subs(it->second == StrToDouble(val)) << std::endl;
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

std::string NatExpressions::natUncerError(NatTrouDuc& traduc, MetaName& vars)
{
	GiNaC::ex eq = this->exp;
	GiNaC::ex sum; //empty exp to concatenate the expression for uncertainties formula			

	for(GiNaC::symtab::const_iterator it = this->table.begin();it != this->table.end(); ++it)
	{
		std::string natvar(traduc[it->first]);
		sum += pow(eq.diff(GiNaC::ex_to<GiNaC::symbol>(it->second))*GiNaC::symbol(vars[natvar]->error),2);

		//TODO CHECK WITH ANOTHER software
	}
	//Put the value of the equation to the resultvar error /\ error value
	//===================================================================
	std::ostringstream s;
	s << sqrt(sum);
	return s.str();
}
