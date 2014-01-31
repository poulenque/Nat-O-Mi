#ifndef natConfi_h
#define natConfig_h

#include <yaml-cpp/yaml.h>
#include "natConpute.h"
#include "natOutput.h"

struct NatConfig{

	//Constructor TODO COMPLETE
	NatConfig(){};

	MetaVar natvar;
	NatData datas;
	MetaExpr natexprs;

	std::vector<NatOutPute> text;
	std::vector<NatOutPute> latex;
	std::vector<NatOutPute> gnuplot;

	bool checkVars();
	bool checkExpr();
	bool checkOutput();

	void printText(bool NatHeader=false);
	void printLaTeX(size_t NatHeader=MIDDLE);
};

#endif
