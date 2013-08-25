#include <fstream>
#include <map> 
#include <algorithm>
#include "vector"
#include <sstream>

std::string minimal_gnuplot_script(std::string inputfile,std::vector<std::string>  argvar, std::map<std::string,size_t> maphead)
{
	std::stringstream gnufile;

	gnufile << "%This file is generated with N@-O-Mi-3.0" << std::endl;//Beurk?
	gnufile << "set terminal context standalone" << std::endl;
	gnufile << "set gnufile '"+inputfile+".tex" << std::endl;
	gnufile << "set title '"+inputfile << std::endl;
	gnufile << "set autoscale" << std::endl;
	gnufile << "set grid" << std::endl;
	gnufile << "set xtics auto" << std::endl;
	gnufile << "set xlabel '"+argvar[0] << std::endl;
	gnufile << "set ylabel '"+argvar[1] << std::endl;
	gnufile << "set ytics auto" << std::endl;
	if(argvar.size()>=3)
	{
		gnufile << "set zlabel '"+argvar[2]<< std::endl;
		gnufile << "set ztics auto"<< std::endl;
	}
	for(unsigned int i(0);i < argvar.size();i++)
		gnufile << argvar[i] << "=" << maphead[argvar[i]] << std::endl;
	return gnufile.str();
}
