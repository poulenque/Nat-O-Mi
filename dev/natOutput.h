#ifndef natOutput_h
#define natOutput_h//TODO CHANGE NAME

#include "natUtils.h"

enum NatOutParam { HEAD=1, MIDDLE, END};

struct NatOutPute{//TODO Faire une classe et utilisé du polymorphisme???

	std::vector<std::string> contents;
	std::string path;
	std::string caption;
	std::string label;
};

std::string minimal_gnuplot_script(std::string inputfile,std::vector<std::string>  argvar, std::map<std::string,size_t> maphead);

#endif
