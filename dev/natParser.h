#ifndef natParser_h
#define natParser_h

#include <yaml-cpp/yaml.h>
#include <ginac/ginac.h>

#include "natUnits.h"
#include "natColors.h"

#define NatErrorSuffix "_error"
#define NatExprPrec 50

struct NatVariable{

	NatVariable();
	NatVariable(const std::string& name,const Unit& unit, const std::string& error);

	std::string name;
	Unit unit;
	std::string error;
	size_t index;
	double value;
};

typedef std::map<std::string, NatVariable*> MetaName;

typedef std::map<std::string, std::ifstream*> NatData;

typedef std::map<std::string,std::string> NatTrouDuc;

struct NatExpressions{

	NatExpressions();
	NatExpressions(const std::string& formula, size_t precision=NatExprPrec);

	double natConPute(NatTrouDuc& traduc, MetaName& vars);
	std::string natUncerError(NatTrouDuc& traduc, MetaName& vars);//CORE IN NATCONPUTE TODO MOVE THIS STRUCT THERE

	//Define the parser, symbol table and exypression to evaluate
	GiNaC::parser reader;
	GiNaC::symtab table;
	GiNaC::ex exp;
	size_t prec;
};

typedef std::map<std::string, NatExpressions*> MetaExpr;

struct NatOutPute{//TODO Faire une classe et utilisé du polymorphisme???
				//ajouter le traduc dans ce cas et les vars

	std::vector<std::string> contents;
	std::string path;
	std::string caption;
	std::string label;
};

struct NatConfig{

	NatConfig();

	void updateMetaNat();
	bool updateVars();
	void printText(bool NatHeader=false);
	void printLaTeX(size_t NatHeader=2);
	void printGNUplot();


	NatTrouDuc traduc;
	MetaName natvar;
	NatData datas;
	MetaExpr natexprs;

	std::vector<NatOutPute> text;
	std::vector<NatOutPute> latex;
	std::vector<NatOutPute> gnuplot;
};


bool natParseNext(std::ifstream* input_file,std::vector<std::string>& output);
bool NatParseNextLines(NatOutPute& output);
std::vector<double> natParseContent(std::vector<std::string> input);

//NatOutPute NatParseConfig(std::string path);
bool natParseConfig(NatConfig& conf , std::string configpath);
bool natParseConfig(std::vector<NatConfig>& out,std::vector<std::string> configpath);

bool natParseHeader(NatConfig& config);
MetaName natParseHeader(std::vector<std::string> input);


std::ostream& operator<<( std::ostream& out, const NatVariable& var);

bool operator>>(const YAML::Node& node, NatConfig& config);
bool operator>>(const YAML::Node& node, NatData& datas);
bool operator>>(const YAML::Node& node, MetaName& vars);
bool operator>>(const YAML::Node& node, std::vector<NatExpressions*>& expr);
bool operator>>(const YAML::Node& node, std::vector<NatOutPute>& vars);

MetaName::const_iterator findPrefix(const MetaName& map, const std::string& search_for);

#endif
