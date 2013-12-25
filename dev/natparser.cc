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



static std::map<std::string, NatData> str2natData;
static std::map<std::string, NatVariable*> str2NatVariable;




//Constructor
NatConfig::NatConfig():datas(){}
NatData::NatData(){}
NatVariable::NatVariable(){}

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

//***************
//Update function
//***************
void NatData::update(){
	//TODO
	//read line and write to readline
}
//*********************
//YAML operator >> Data
//*********************
bool operator>>(const YAML::Node& node, std::vector<NatData>& datas){

	NatData data;//declared once here because push_back makes a copy
	string path;
	bool ret=true;


	for(size_t i=0 ; i< node.size(); i++){
	
		datas.push_back(data);
		//====================================
		node[i]["name"]>>datas.back().name;
		//====================================
		if(str2natData.find(datas.back().name)!=str2natData.end()){
			cout
			<<CONSOL_RED_TEXT   <<"ERROR : (line"
			<<CONSOL_CYAN_TEXT  << 666
			<<CONSOL_RED_TEXT   << ") you cannot name two datas with the same name ("
			<<CONSOL_CYAN_TEXT  <<datas.back().name
			<<CONSOL_RED_TEXT   <<") !\n"
			<<CONSOL_NORMAL_TEXT;

			ret=false;
		}
		//====================================
		node[i]["path"]>>path;

		boost::filesystem::path abs_path = boost::filesystem::complete(path);
		std::string path = abs_path.string();

		datas.back().file = new ifstream(path);

		if(!datas.back().file->is_open()){

			cout
			<<CONSOL_RED_TEXT   <<"ERROR : (line"
			<<CONSOL_CYAN_TEXT  << 666
			<<CONSOL_RED_TEXT   <<") cannot open "
			<<CONSOL_CYAN_TEXT  <<path
			<<CONSOL_RED_TEXT   <<" !\n"
			<<CONSOL_NORMAL_TEXT;

			ret=false;

		}else
		{
			std::vector<std::string> data_line;
			//trouver la ligne avec les noms de variable
			if(!natParseNext(datas.back().file,data_line)){
				cout<<CONSOL_RED_TEXT<<"\""<<CONSOL_CYAN_TEXT<<*datas.back().file
				<<CONSOL_RED_TEXT<<"\" is empty."<<endl;
				ret=false;
			}
			//Parsing Header Files of datas en then mapping variables
			//=======================================================
			datas.back().variables = natParseHeader(data_line);
		}
		//====================================
		//map str2natData
		//equivalent to:
		//str2natData[datas.back().name]=&datas.back();
		str2natData.insert( pair<string,NatData>( datas.back().name , datas.back()));
	}
	return ret;
}
//*************************
//YAML operator >> Variable
//*************************
bool operator>>(const YAML::Node& node, std::vector<MetaName>& vars){

	MetaName var;
	string str;
	string str2;
	string str3;
	bool ret = true;
	for(size_t i=0 ; i< node.size(); i++){

		vars.push_back(var);
		//=========================================================
		// std::string name;
		node[i]["varname"]>>vars.back();
		if(str2natData.find(vars.back())!=str2natData.end())
		{
			cout
			<<CONSOL_RED_TEXT<<"ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") you cannot name two variables with the same name ("
			<<CONSOL_CYAN_TEXT<<vars.back()
			<<CONSOL_RED_TEXT<<") !"
			<<endl<<CONSOL_NORMAL_TEXT;
			cout.flush();
			ret=false;
		}
		//=========================================================
		//NatData* data;
		//Check if var or expr exists, else it stops
		if(node[i].FindValue("var"))
		{
			node[i]["var"]>>str;
			size_t pos = str.find("::");
			str2 = str.substr (0,pos);
			str3 = str.substr (pos+2);// avoid the "::"

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
			else if(str2natData.find(str2)==str2natData.end())
			{
				cout
				<<CONSOL_RED_TEXT<<"ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") data "
				<<CONSOL_CYAN_TEXT<<str2
				<<CONSOL_RED_TEXT<<" does not exist !"<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;
			}
			else if(str2NatVariable.find(str3)==str2NatVariable.end())
			{
				cout
				<<CONSOL_RED_TEXT<<"ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") var "
				<<CONSOL_CYAN_TEXT<<str3
				<<CONSOL_RED_TEXT<<" does not exist !"<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;
			}
			//TODO CECI EST DANGEREUX ET SANS EFFETS!
			if(str2NatVariable[str3] !=NULL)
				str2NatVariable[str3]->varname = vars.back();
		}
		//=========================================================
		//Expr;
		else if(node[i].FindValue("expr"))
		{
			//TODO
			node[i]["expr"]>>str;
			//GiNaC::ex(str,vars.back().expr);
		}
		else
		{
			std::cout << "Pas de node 'var' ou 'expr' trouvé!" << std::endl;
			exit(1);
		}
	}
	return ret;	
}
//************************
//YAML operator >> Outputs
//************************
bool operator>>(const YAML::Node& node, std::vector<NatOutPute>& outs){
	
	NatOutPute out;
	bool ret=true;
	for(size_t i=0 ; i< node.size(); i++){
		//===================================
		outs.push_back(out);
	
		//====================================
		node[i]["path"]>>outs.back().path;
		//====================================
		const YAML::Node& content_node = node[i]["content"];
	 	for(unsigned j = 0; j < content_node.size(); j++)
		{
			std::string content;
	 		content_node[j] >> content;
	 		outs.back().contents.push_back(content);
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
	if(! (node["variables"] >> config.natvar))
		ret= false;
	if(! (node["text"] >> config.text))
		ret= false;
	if(! (node["latex"] >> config.latex))
		ret= false;
	if(! (node["gnuplot"] >> config.gnuplot))
		ret= false;


	cout << " GIGA TEST " << config.datas[0].variables[0].varname << std::endl;
	return ret;
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

	boost::char_separator<char> sep(" \t");
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
std::vector<NatVariable> natParseHeader(vector<std::string> input){

	cout<<CONSOL_LIGHTGRAY_TEXT
	<<"! HEADER PARSE !"<<endl
	<<"^^^^^^^^^^^^^^^^"<<endl;

	vector<NatVariable> c;
	for(auto & t:input){
		NatVariable n;

		size_t i=0;
		while(i<t.size() && t[i]!='['){
			n.name.push_back(t[i]);
			i++;
		}
		//=======================
		//=======================
		if(i>=t.size()){
			cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<CONSOL_RED_TEXT<<"OMG you can't be a physicist ! \""<<CONSOL_CYAN_TEXT<< n.name
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
			n.unit = str2unit(str);
		}
		i++;
		//=======================
		//=======================
		if(i>=t.size()){
			cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<CONSOL_RED_TEXT<<"No error ?! Are you kidding me ?\""<<CONSOL_CYAN_TEXT<< n.name
			<<CONSOL_RED_TEXT<<"\"\'s"<<" error estimation is missing !!!\n"<<CONSOL_NORMAL_TEXT;
			exit(0);//<-- whoa this is hardcore ! But how could you mesure something with no error ? HOW ???
		}
		if(i<t.size() && t[i]=='['){
			i++;
			while(i<t.size() && t[i]!=']'){
				n.error.push_back(t[i]);
				i++;
			}
		}
		i++;

		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"read    : "<<CONSOL_CYAN_TEXT<<t<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"name    : "<<CONSOL_NORMAL_TEXT<<n.name<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"unit    : "<<CONSOL_NORMAL_TEXT<<n.unit<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"error   : "<<CONSOL_NORMAL_TEXT<<n.error<<endl;
		//cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"expr : "<<CONSOL_NORMAL_TEXT<<n.expr<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"-->"<<"==================="<<endl;

		//map str2NatVariable
		//equivalent to:
		//str2NatVariable[vars.back().name]=&vars.back();
		str2NatVariable.insert( pair<std::string,NatVariable*>( n.name , &n));
		c.push_back(n);
	}

	cout<<CONSOL_LIGHTGRAY_TEXT
	<<"! HEADER PARSE !"<<CONSOL_MAGENTA_TEXT<<" --> DONE"<<endl;
	return c;
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
