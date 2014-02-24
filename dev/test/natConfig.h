#ifndef natConfi_h
#define natConfig_h

#include "natExpr.h"
#include "natOutput.h"

struct NatConfig{

	NatConfig(bool debug=false);
	~NatConfig();

	bool debug;

	MetaVar natvar;
	NatData datas;
	MetaExpr natexprs;

	std::vector<NatOutPute> text;
	std::vector<NatOutPute> latex;
	std::vector<NatOutPute> gnuplot;

	bool checkVars();
	bool checkExpr();
	bool checkOutput();

	void computeVars();

	void printText(bool NatHeader=false);
	void printLaTeX(size_t NatHeader=MIDDLE);
};

#endif
