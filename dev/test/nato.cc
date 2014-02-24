#include "nato.h"

//*************************
//Constructor && Destructor
//*************************
natOmi::natOmi(bool d):debug(d){}


//****************************************
//Parsing several configuration files YAML
//****************************************
bool natOmi::natParseConfig(std::vector<NatConfig*>& out, vector<std::string>& configpath){
	for(size_t i=0;i<configpath.size();i++){
		NatConfig* conf = new NatConfig(this->debug);
		if(!natParseConfig(*conf,configpath[i]))
			return false;
		out.push_back(conf);
	}
	return true;
}

//**************************************
//Parsing unique configuration file YAML
//**************************************
bool natOmi::natParseConfig(NatConfig& conf, string& configpath)
{
	bool ret(true);

	ifstream yamlfile(configpath);

	if(!yamlfile.is_open()){
		cout<<CONSOL_RED_TEXT<<"could not open file "<<CONSOL_CYAN_TEXT<<configpath<< endl;
		ret = false;
	}

	//YAML Parsing
	//************
	YAML::Parser parser(yamlfile);
	YAML::Node doc;
	parser.GetNextDocument(doc);
	if(!(doc>>conf))
		ret = false;

	//Data Files Parsing
	//******************
	if(!natParseHeader(conf))
		ret = false;

	//Config checking
	//***************
	if(!conf.checkVars())
		ret = false;
	
	if(!conf.checkExpr())
		ret = false;

	cout << "out of expr" << endl;
	if(!conf.checkOutput())
		ret = false;

	return ret;
}

//***********************
//NatOmI update vars Func
//***********************
bool updateVars(NatConfig* conf)
{
	bool ret(true);
	//update var_value;//global so there is no mistakes
	//=================================================
	for(NatData::iterator it = conf->datas.begin(); it != conf->datas.end(); ++it)
	{
		if(!it->second.updateVars())
			ret=false;
	}
	return ret;//TODO works only with data with seme lines number
}
