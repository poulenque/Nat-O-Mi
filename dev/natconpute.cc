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

GiNaC::ex natUncerError(const std::string& formula, const std::vector<NatVariable>& data_vars, std::map<std::string,size_t> dataName_str2num)
{

	GiNaC::parser reader;
	GiNaC::symtab table;
	GiNaC::ex e;
	GiNaC::ex sum; //empty exp to concatenate the expression ofr uncertainties formula
		
	e = reader(formula);
	table = reader.get_syms();
			
	for(GiNaC::symtab::const_iterator it = table.begin();
		it != table.end(); ++it)
	{
		size_t id(dataName_str2num[it->first]);
		
		/*std::cout << "The derivative of " << e << " with respect to " << it->first << " is: ";
		std::cout << e.diff(GiNaC::ex_to<GiNaC::symbol>(it->second)) << "." << std::endl;
		std::cout << "error " << data_info[id].error << std::endl;
		std::cout << "[(d" <<  data_info[id].name << "/d" << it->second << ")*error";
		std::cout << data_info[id].name << "]^2= ";
		std::cout << pow(e.diff(GiNaC::ex_to<GiNaC::symbol>(it->second))*GiNaC::ex(StrToDouble(data_info[id].error)),2) << std::endl;*/

		sum += pow(e.diff(GiNaC::ex_to<GiNaC::symbol>(it->second))*GiNaC::symbol(data_vars[id].error),2);
	}
	return sqrt(sum);//uncertainties formula
}
