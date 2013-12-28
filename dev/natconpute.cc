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
void NatExpressions::natConPute(NatTrouDuc& traduc, MetaName& vars)
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

	//Put the value of the equation to the resultvar
	//==============================================
	std::ostringstream s;
	s << eq;
	vars[traduc[this->resultvar]]->value = s.str();
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

void NatExpressions::natUncerError(NatTrouDuc& traduc, MetaName& vars)
{
	GiNaC::ex eq = this->exp;
	GiNaC::ex sum; //empty exp to concatenate the expression for uncertainties formula			

	for(GiNaC::symtab::const_iterator it = this->table.begin();it != this->table.end(); ++it)
	{
		std::string natvar(traduc[it->first]);
		std::cout << traduc[it->first] << std::endl;
		sum += pow(eq.diff(GiNaC::ex_to<GiNaC::symbol>(it->second))*GiNaC::symbol(vars[natvar]->error),2);

		//TODO CHECK WITH ANOTHER software
		std::cout << "The derivative of " << eq << " with respect to " << it->first << " is: ";
		std::cout << eq.diff(GiNaC::ex_to<GiNaC::symbol>(it->second)) << "." << std::endl;
		std::cout << "error " << vars[natvar]->error << std::endl;
		std::cout << "[(d" <<  vars[natvar]->name << "/d" << it->second << ")*error";
		std::cout << vars[natvar]->name << "]^2= ";
		std::cout << pow(eq.diff(GiNaC::ex_to<GiNaC::symbol>(it->second))*GiNaC::symbol(vars[natvar]->error),2) << std::endl;
		std::cout << sqrt(sum) << " " << sqrt(sum).evalf() <<std::endl;
	}
	//Put the value of the equation to the resultvar error /\ error value
	//===================================================================
	std::ostringstream s;
	s << sqrt(sum);
	//vars[traduc[this->resultvar+NatErrorSuffix]]->expr = s.str();
}
