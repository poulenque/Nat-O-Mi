#include <fstream>
#include <map> 
#include <algorithm>
#include "vector"
#include <sstream>

std::string textable_init(std::vector<std::string>  line);
std::string textable_content(std::vector<std::string>  line);
std::string textable_end();


std::string textable_init(std::vector<std::string>  line, std::string caption, std::string label)
{
	std::stringstream tablefile;
  	
	tablefile << "%This file is generated with N@-O-Mi-3.0" << std::endl;//Beurk?

	tablefile << "\\begin{table}[h]" << std::endl;
	tablefile << "\t\\caption{"<< caption << "}" << "\\label{tab:" << label << "}" << std::endl;
	tablefile << "\t\t\\begin{tabular}{";
	for(unsigned int i(0);i < line.size();tablefile << "|l",i++);
	tablefile << "|}" << std::endl;
	tablefile << "\t\t\\hline" << std::endl;//tab maybe

	tablefile <<textable_content(line);//print the first line
	return tablefile.str();
}

std::string textable_content(std::vector<std::string>  line)
{
	std::stringstream tablefile;

	tablefile << "\t\t";
	for(unsigned int i(0);i < line.size()-1;tablefile << line[i] << " & ",i++);
	tablefile << line[line.size()-1] << "\\\\" << " \\hline"<< std::endl;

	return tablefile.str();
}

std::string textable_end()
{
	std::stringstream tablefile;

	tablefile << "\t\t\\hline" << std::endl;
	tablefile << "\t\\end{tabular}" << std::endl;
	tablefile << "\\end{table}" << std::endl;

	return tablefile.str();
}
