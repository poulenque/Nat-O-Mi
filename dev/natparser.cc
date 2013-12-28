#include "consol_color.h"
#include "natparser.h"

#include <iostream>
#include <string>
#include <sstream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

const string commentSymbol = "#";

using namespace std;



static NatTrouDuc metoname;


//Constructor TODO COMPLETE
NatConfig::NatConfig(){}
NatExpressions::NatExpressions(){}
NatVariable::NatVariable(){}
NatVariable::NatVariable(const std::string& n,const Unit& u, const std::string& e):
name(n),unit(u),error(e){}


//****************************************
//Parsing several configuration files YAML
//****************************************
bool natParseConfig(std::vector<NatConfig>& out,std::vector<std::string> configpath){
	for(size_t i=0;i<configpath.size();i++){
		NatConfig conf;
		if(!natParseConfig(conf,configpath[i]))
			return false;
		out.push_back(conf);
	}
	return true;
}
//**************************************
//Parsing unique configuration file YAML
//**************************************

bool natParseConfig(NatConfig& conf, std::string configpath){

	std::ifstream read(configpath);

	if(!read.is_open()){
		cout<<CONSOL_RED_TEXT<<"could not open file "<<CONSOL_CYAN_TEXT<<configpath<< endl;
		return false;
	}

	YAML::Parser parser(read);
	YAML::Node doc;
	parser.GetNextDocument(doc);

	doc>>conf;

	return true;
}
//*********************
//YAML operator >> Data
//*********************
bool operator>>(const YAML::Node& node, NatData& datas){

	bool ret=true;
	string path;
	std::string name;
	std::ifstream* file;

	for(size_t i=0 ; i< node.size(); i++){

		//====================================
		node[i]["name"]>>name;
		//====================================
		if(datas.find(name)!=datas.end()){
			cout
			<<CONSOL_RED_TEXT   <<"ERROR : (line"
			<<CONSOL_CYAN_TEXT  << 666
			<<CONSOL_RED_TEXT   << ") you cannot name two datas with the same name ("
			<<CONSOL_CYAN_TEXT  <<name
			<<CONSOL_RED_TEXT   <<") !\n"
			<<CONSOL_NORMAL_TEXT;
	
			ret=false;
		}
		//====================================
		node[i]["path"]>>path;

		boost::filesystem::path abs_path = boost::filesystem::complete(path);
		path = abs_path.string();
		file = new ifstream(path);

		if(!file->is_open()){

			cout
			<<CONSOL_RED_TEXT   <<"ERROR : (line"
			<<CONSOL_CYAN_TEXT  << 666
			<<CONSOL_RED_TEXT   <<") cannot open "
			<<CONSOL_CYAN_TEXT  <<path
			<<CONSOL_RED_TEXT   <<" !\n"
			<<CONSOL_NORMAL_TEXT;

			ret=false;
		}
		//====================================
		//map str2natData
		//equivalent to:
		//str2natData[datas.back().name]=&datas.back();
		datas.insert( pair<string, ifstream*>( name , file));
	}
	return ret;
}
//*************************
//YAML operator >> Variable
//*************************
bool operator>>(const YAML::Node& node, MetaName& vars){

	string str;
	string str2;
	string str3;
	std::string name;
	bool ret = true;
	for(size_t i=0 ; i< node.size(); i++)
	{

		//Check if the varname is already used
		//====================================
		node[i]["name"]>>name;
		if(vars.find(name)!=vars.end())//TODO switch?
		{
			cout
			<<CONSOL_RED_TEXT<<"ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") you cannot name two variables with the same name ("
			<<CONSOL_CYAN_TEXT<<name
			<<CONSOL_RED_TEXT<<") !"
			<<endl<<CONSOL_NORMAL_TEXT;
			cout.flush();
			ret=false;
		}
		node[i]["in"]>>str;
		size_t pos = str.find("::");
		str2 = str.substr (0,pos);
		str3 = str.substr (pos+2);// avoid the "::"

		//*************** PRINTS ****************
		//***************************************
		//Check if var exists in the global table
		//=======================================
		if(pos==string::npos)
		{
			cout
			<<CONSOL_RED_TEXT<<"ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") variable "
			<<CONSOL_CYAN_TEXT<<str
			<<CONSOL_RED_TEXT<<"\'s data missing (format should be myData::var)"<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;
		}
		//Checks if data exist
		//====================
		else if(findPrefix(vars, str2)==vars.end())
		{
			cout
			<<CONSOL_RED_TEXT<<"ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") data "
			<<CONSOL_CYAN_TEXT<<str2
			<<CONSOL_RED_TEXT<<" does not exist!"<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;
		}
		//Check if the variable exists in data
		//====================================
		else if(vars.find(str)==vars.end())
		{
			cout
			<<CONSOL_RED_TEXT<<"ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") var "
			<<CONSOL_CYAN_TEXT<<str3
			<<CONSOL_RED_TEXT<<" does not exist, in data:"
			<<CONSOL_CYAN_TEXT<<str2
			<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;//FAIRE DES EXIT(0) plus cool TODO
		}
		//Check if any vars has been redefined
		//====================================
		else if(metoname.find(str3)!=metoname.end())
		{
			cout
			<<CONSOL_RED_TEXT<<"ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") var "
			<<CONSOL_CYAN_TEXT<<str3
			<<CONSOL_RED_TEXT<<" has been redifined"
			<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;//FAIRE DES EXIT(0) plus cool TODO
		}	
		else
		{
			//Mapping the string name of meta name to corresponding var
			//=========================================================
			metoname.insert( pair<string,string>(name , str));
			metoname.erase(str);
		}
	}
	return ret;	
}
//****************************
//YAML operator >> Expressions
//****************************
bool operator>>(const YAML::Node& node, std::vector<NatExpressions*>& exprs)
{
	std::string name;
	std::string formula;
	bool ret=true;
	for(size_t i=0 ; i< node.size(); i++){

		NatExpressions* natexpr = new NatExpressions;
		//===================================
		node[i]["name"]>>natexpr->resultvar;

		//************* EXPRESSIONS *************
		//***************************************
		//=================================== //TODO CONVERT STR To GINAC
		node[i]["expr"]>>formula;	
		//===================================

		natexpr->exp = natexpr->reader(formula);
		//Get the symbol from the expression and write it down to a table
		natexpr->table = natexpr->reader.get_syms();

		//Look if all the vars has been declared previously
		//=================================================
		for(GiNaC::symtab::iterator it = natexpr->table.begin();
			it != natexpr->table.end(); ++it)
		{
			if(metoname.find(it->first)==metoname.end())//FAIRE UNE FONCTION TEST TODO
			{	
				cout
				<<CONSOL_RED_TEXT<<"ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") Natvar "
				<<CONSOL_CYAN_TEXT<<it->first
				<<CONSOL_RED_TEXT<<" does not exist"
				<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;//FAIRE DES EXIT(0) plus cool TODO
			}
		}
		//===================================
		exprs.push_back(natexpr);

		//Insert the new variable into the tmp traduc map
		//===============================================
		metoname.insert( pair<string,string>(natexpr->resultvar , natexpr->resultvar));
	}
	return ret;
}
//************************
//YAML operator >> Outputs
//************************
//TODO FINNISH
bool operator>>(const YAML::Node& node, std::vector<NatOutPute>& outs){
	
	NatOutPute out;
	string path;
	bool ret=true;
	for(size_t i=0 ; i< node.size(); i++){

		//===================================
		outs.push_back(out);
		//====================================
		node[i]["path"]>>path;
		ofstream output(path);

		if(!output.is_open())//TODO VERIFIER QU'IL N ECRASE PAS UN FICHIER EXISTANT
		{
			cout<<CONSOL_RED_TEXT<<"could not open file"<<CONSOL_CYAN_TEXT<<path<< endl<<CONSOL_NORMAL_TEXT;
			ret=false;
		}
		outs.back().path = path;
		//====================================
		const YAML::Node& content_node = node[i]["content"];
	 	for(unsigned j = 0; j < content_node.size(); j++)
		{
			std::string content;
	 		content_node[j] >> content;
	 		outs.back().contents.push_back(content);

			if(metoname.find(content)==metoname.end())//FAIRE UNE FONCTION TEST TODO
			{	
				cout
				<<CONSOL_RED_TEXT<<"ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") Natvar "
				<<CONSOL_CYAN_TEXT<<content
				<<CONSOL_RED_TEXT<<" does not exist"
				<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;//FAIRE DES EXIT(0) plus cool TODO
			}
		}
	}
	return ret;
}
//***********************
//YAML operator >> Config
//***********************
bool operator>>(const YAML::Node& node, NatConfig& config){

	bool ret=true;

	if(! (node["data"]>> config.datas))
		ret= false;

	//Parsing files to check
	//======================
	if(!natParseHeader(config))
		ret = false;

	if(! (node["variables"] >> config.natvar))
		ret= false;
	if(! (node["expressions"] >> config.natexprs))
		ret= false;

	//Refreshing all maps for checks
	//==============================
	config.updateMaps(metoname);


	if(node.FindValue("text")){
		if(!(node["text"] >> config.text))
			ret= false;
	}
	if(node.FindValue("latex")){
		if(! (node["latex"] >> config.latex))
			ret= false;
	}
	if(node.FindValue("gnuplot")){
		if(! (node["gnuplot"] >> config.gnuplot))
			ret= false;
	}	
	return ret;
}
//***********************
//Config update Maps Func
//***********************
void NatConfig::updateMaps(const NatTrouDuc& map)
{
	//Copy translator
	//===============
	this->traduc.insert(map.begin(), map.end());

	//Add vars from Node expression to VarsMap
	//========================================
	for(NatTrouDuc::const_iterator it = map.begin();it != map.end(); ++it)
	{
		if(this->natvar.find(it->second)==this->natvar.end())
			this->natvar.insert(pair<string,NatVariable*>(it->second, new NatVariable(it->second, Unit(), "*")));}
}
//***********************
//Config update vars Func
//***********************
bool NatConfig::updateVars()
{
	std::vector<std::string> data_line;

	//update var_value;//global so there is no mistakes
	//=================================================
	for(NatData::iterator it = this->datas.begin(); it != this->datas.end(); ++it)
	{
		if(!natParseNext(it->second,data_line))
			return false;


		//Check if there is the good number of columns
		//============================================
		//TODO FIND BETTER ALGORYTHM WITH A NEW MAP OR RECHANGE STRUCT VARS
		//OR PLACING HINTS IN THE MAP
		size_t varcount(0);
		for(MetaName::iterator it2 = this->natvar.begin(); data_line.size()<=varcount, it2 != this->natvar.end();it2++)
		{
			if(it2->first.find(it->first)==0)//slow
			{
				it2->second->value=data_line[it2->second->index];
				varcount++;
			}
		}

		//Check if there is the good number of columns
		//============================================
		if(data_line.size()!=varcount)
		{
			std::cout 	
			<< CONSOL_RED_TEXT  << "The line "
			<< CONSOL_CYAN_TEXT <<"xxx"
			<<CONSOL_RED_TEXT <<" has incorrect number of columns" 
			<< std::endl;
			return false;
		}
		//Cleaning the data_line to avoid conflicts:
		data_line.clear();
	}		
	return true;
}
//***************************
//NatConfig printings methods
//***************************
void NatConfig::printText(bool NatHeader)
{
	for(size_t j(0);j <  this->text.size();j++)
	{
		//Opening the outputfile //TODO check for errors in opening for ret value
		std::ofstream output(this->text[j].path, ios_base::app);

		//Only the first time, writing the heading files
		if(NatHeader)
		{
			for(size_t k(0);k <  this->text[j].contents.size();k++)
				output << *this->natvar[this->traduc[this->text[j].contents[k]]] << " " ;
		}
		else
		{	for(size_t k(0);k <  this->text[j].contents.size();k++)
				output << this->natvar[this->traduc[this->text[j].contents[k]]]->value << " " ;//TODO ASK FOR SEPERATOR
		}
		
		output << std::endl;
		output.close();
	}
}

//TODO,NB: GiNaC allows to print in latex format
//Could be cool!
void NatConfig::printLaTeX(bool NatHeader)
{
	//TODO soon

}
void NatConfig::printGNUplot()
{
	//TODO???????????????

}
//***********************
//Cout operator << Output
//***********************
std::ostream& operator<<( std::ostream& out, const NatVariable& var)
{
	out << var.name << "[" << var.unit << "]" << "[" << var.error << "]";
	return out;
}

//***********************
//NATOMI HEADER PARSE
//***********************

//!!!!!!!!!!!!attention!!!!!!!!!!!!!!
// le cas ou un fermant est a gauche d'un mot n'est pas gere!
//
// le cas :
//
// U[V][0.2 ]hauteur[m][1] 
//          ^
//
// n'est traite correctement
//
vector<string> natParse_str2vector(string read_line){
	vector<string> v;

	boost::char_separator<char> sep(" \t");//TODO PRECISE THE SEPARATOR
	boost::tokenizer<boost::char_separator<char>> tokens(read_line, sep);

	bool inside=false;

	for (const auto& t : tokens){
		if(inside){
			v[v.size()-1]+=t;
			if(t[t.size()-1]==']')
				inside=false;
		}else{
			//si on passe a l'interieur...
			if(t[0]=='['){
				v[v.size()-1]+=t;
				//...mais qu'on ne sort pas
				if(t[t.size()-1]!=']')
					inside=true;//on passe en mode interieur.
			}else{
				v.push_back(t);
				if(t[t.size()-1]=='[')
					inside=true;
			}

		}
	}

	return v;
}

//TODO
//
//Complete missing things : calculate Unit
//check Units is formulae
//
//weird stuff like [[] or []]
//error in % or %0 or constant or variable
//check end with ]
MetaName natParseHeader(vector<std::string> input){

	cout<<CONSOL_LIGHTGRAY_TEXT
	<<"! HEADER PARSE !"<<endl
	<<"^^^^^^^^^^^^^^^^"<<endl;

	MetaName varmap;
	size_t index(0);
	for(auto & t:input){
		NatVariable* n = new NatVariable();

		size_t i=0;
		while(i<t.size() && t[i]!='['){
			n->name.push_back(t[i]);
			i++;
		}
		//=======================
		//=======================
		if(i>=t.size()){
			cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<CONSOL_RED_TEXT<<"OMG you can't be a physicist ! \""<<CONSOL_CYAN_TEXT<< n->name
			<<CONSOL_RED_TEXT<<"\"\'s"<<" Unit are missing !!! are you mad ?\n"<<CONSOL_NORMAL_TEXT;
			exit(0);//<-- whoa this is hardcore ! But no unit = kill yourself.
		}
		if(t[i]=='['){
			i++;
			string str;
			while(i<t.size() && t[i]!=']'){
				str.push_back(t[i]);
				i++;
			}
			n->unit = str2unit(str);
		}
		i++;
		//=======================
		//=======================
		if(i>=t.size()){
			cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<CONSOL_RED_TEXT<<"No error ?! Are you kidding me ?\""<<CONSOL_CYAN_TEXT<< n->name
			<<CONSOL_RED_TEXT<<"\"\'s"<<" error estimation is missing !!!\n"<<CONSOL_NORMAL_TEXT;
			exit(0);//<-- whoa this is hardcore ! But how could you mesure something with no error ? HOW ???
		}
		if(i<t.size() && t[i]=='['){
			i++;
			while(i<t.size() && t[i]!=']'){
				n->error.push_back(t[i]);
				i++;
			}
		}
		i++;
	
		n->index = index;
		index++;

		//===========================================================================
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"read    : "<<CONSOL_CYAN_TEXT<<t<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"name    : "<<CONSOL_NORMAL_TEXT<<n->name<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"unit    : "<<CONSOL_NORMAL_TEXT<<n->unit<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"error   : "<<CONSOL_NORMAL_TEXT<<n->error<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"index : "<<CONSOL_NORMAL_TEXT<<n->index<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"-->"<<"==================="<<endl;

		//===========================================================
		varmap.insert( pair<std::string,NatVariable*>( n->name , n));
	}

	cout<<CONSOL_LIGHTGRAY_TEXT
	<<"! HEADER PARSE !"<<CONSOL_MAGENTA_TEXT<<" --> DONE"<<endl;
	return varmap;
}

// ouput -> next not commented line as vector<string>
bool natParseNext(ifstream* input_file,vector<string>& output){

	string read_line;

	while(output.size()==0 && input_file->good()){
		getline(*input_file,read_line);
		output = natParse_str2vector(read_line);

		//if this line was actually a comment...
		if(output.size() && commentSymbol==output[0].substr(0,commentSymbol.size())){
			//do ignore that line
			output=vector<string>();
		}
	}
	if(output.size())
		return true;
	return false;
}

bool natParseHeader(NatConfig& config)
{
	bool ret=true;
	std::vector<std::string> data_line;
	for( NatData::iterator it = config.datas.begin(); it != config.datas.end(); ++it )
	{
		//trouver la ligne avec les noms de variable
		if(!natParseNext(it->second,data_line)){
			cout<<CONSOL_RED_TEXT<<"\""<<CONSOL_CYAN_TEXT<<*it->second
			<<CONSOL_RED_TEXT<<"\" is empty."<<endl;
			ret=false;
		}

		//Parsing Header Files of datas en then mapping variables
		//=======================================================
		MetaName tmp_map = natParseHeader(data_line);
		for( MetaName::iterator it2 = tmp_map.begin(); it2 != tmp_map.end(); ++it2 )
		{	config.natvar.insert(pair<string, NatVariable*>(it->first+"::"+it2->first, it2->second));
			metoname.insert(pair<string, string>(it->first+"::"+it2->first, it->first+"::"+it2->first));
		}

		//Cleaning the data_line to avoid conflicts:
		data_line.clear();
	}
	return ret;
}


//TODO move somewhere else with other stuff? template??
//*******************************
//Function to find prefix of maps
//*******************************
MetaName::const_iterator findPrefix(const MetaName& map, const string& search_for) {
    MetaName::const_iterator i = map.lower_bound(search_for);
    if (i != map.end()) {
        const string& key = i->first;
        if (key.compare(0, search_for.size(), search_for) == 0) // Really a prefix?
            return i;
    }
    return map.end();
}
