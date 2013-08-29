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
void natConPute(const std::vector<natInfo>& data_info, std::vector<std::string>& line, map<std::string,size_t> dataName_str2num)
{

    GiNaC::symtab table;
	for(unsigned int i(0); i < data_info.size(); i++)
    {	
		if(!std::isnan(StrToDouble(line[dataName_str2num[data_info[i].name]])))
			table[data_info[i].name] = StrToDouble(line[dataName_str2num[data_info[i].name]]);
		//std::cout << data_info[i].name << i << " " << table[data_info[i].name] << " " << StrToDouble(line[dataName_str2num[data_info[i].name]]) << std::endl;
	}

    GiNaC::parser reader(table);
	for(unsigned int i(0); i < data_info.size(); i++)
	{
		if(!data_info[i].formula.empty())
		{
			GiNaC::ex e = reader(data_info[i].formula);
			//std::cout << e << " " << line[dataName_str2num[data_info[i].name]] << std::endl;
			if (GiNaC::is_a<GiNaC::numeric>(e))
            	line[dataName_str2num[data_info[i].name]] = double2str(GiNaC::ex_to<GiNaC::numeric>(e).to_double());
			//std::cout << e << " " << line[dataName_str2num[data_info[i].name]] << std::endl;
		}
	}
}


void natDerive(const std::vector<natInfo>& data_info, std::vector<std::string>& line, map<std::string,size_t> dataName_str2num)
{

	GiNaC::parser reader;

	for(unsigned int i(0); i < data_info.size(); i++)
	{
		if(!data_info[i].formula.empty())
		{
			GiNaC::ex e = reader(data_info[i].formula);
			GiNaC::symtab table = reader.get_syms();

			GiNaC::symbol I = table.find("VolumeH") != table.end() ?
     			   GiNaC::ex_to<GiNaC::symbol>(table["VolumeH"]) : GiNaC::symbol("VolumeH");

			std::cout << "The derivative of " << e << " with respect to VolumeH is: ";
			std::cout << e.diff(I) << "." << std::endl;
		}
	}
}
