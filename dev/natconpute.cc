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
GiNaC::ex natConPute(const std::string& formula, std::vector<std::string>& line, std::map<std::string,size_t> dataName_str2num)
{
	//Define the parser, symbol table and exypression to evaluate
    GiNaC::parser reader;
	GiNaC::symtab table;
	GiNaC::ex e = reader(formula);
	//Get the symbol from the expression and write it down to a table
	table = reader.get_syms();

	//Substitue each variable by its actual value from the line
	for(GiNaC::symtab::iterator it = table.begin();
		it != table.end(); ++it)
	{
		size_t id(dataName_str2num[it->first]);

		if(!std::isnan(StrToDouble(line[id])))
			e = e.subs(it->second == StrToDouble(line[id]));		
		//std::cout << e << " =>" << e.subs(it->second == StrToDouble(line[id])) << std::endl;
	}
	//Results/evaluation of the expression after substituing
	
	return e;
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
