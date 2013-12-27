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



static 	std::map<std::string,std::string> datatovar;


//Constructor
NatConfig::NatConfig(){}
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
		//Check if var or expr exists, else it stops
		//==========================================
		if(node[i].FindValue("in"))
		{
			node[i]["in"]>>str;
			size_t pos = str.find("::");
			str2 = str.substr (0,pos);
			str3 = str.substr (pos+2);// avoid the "::"

			//Special, checks if var is in data and keep the boolean
			//======================================================
			bool redefinition=false;

			//Equivalent to datatovar[str2]
   			 pair <multimap<string,string>::iterator, multimap<string,string>::iterator> checker = datatovar.equal_range(str2);
			for(multimap<string,string>::iterator it=checker.first; it!=checker.second; ++it)
			{
				if(it->second==str3)
				{
					//Mapping the string name of datas to collection of vars  meta name
					//=================================================================
					datatovar.insert( pair<string,string>(str2 , str2+"::"+name));
 					datatovar.erase(it);
					break;//TODO beurk?
				}
				else if(vars.find(str)==vars.end())
					redefinition=true;
			}

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
			else if(datatovar.find(str2)==datatovar.end())
			{
				cout
				<<CONSOL_RED_TEXT<<"ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") data "
				<<CONSOL_CYAN_TEXT<<str2
				<<CONSOL_RED_TEXT<<" does not exist!"<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;
			}
			//Use the previous bool result to print if var exists in data
			//===========================================================
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
			//Use the previous bool result to print if var is re-renamed in config
			//====================================================================
			else if(redefinition)
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
				//vars.insert( pair<string,NatVariable*>(name , vars[str]));
 				//vars.erase(str);
			}
		}//=========================================================
		if(node[i].FindValue("expr") && ret)
		{
			//==================================== //TODO CONVERT STR To GINAC
			//node[i]["expr"]>>vars[name]->expr;
		}
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

		if(!output.is_open())
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
	if(!natParseHeader(config))//Parsing files to check
		ret = false;
	if(! (node["variables"] >> config.natvar))
		ret= false;

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

for( 	std::multimap<std::string,std::string>::iterator it = datatovar.begin(); it != datatovar.end(); ++it)
	cout << it->first << " " << it->second << endl;

	return ret;
}

//***********************
//Config update vars Func
//***********************
void NatConfig::updateVars()
{
	//	foreach output_text, output_latex, output_gnuplot
	std::vector<std::string> data_line;
	//update var_value;//global so there is no mistakes
	for( NatData::iterator it = this->datas.begin(); it != this->datas.end(); ++it)
	{
		natParseNext(it->second,data_line);//TODO wierd wierd avoid the bool return

		//Equivalent to datatovar[it->first]
		pair <multimap<string,string>::iterator, multimap<string,string>::iterator> checker = datatovar.equal_range(it->first);
		for(multimap<string,string>::iterator it2=checker.first; it2!=checker.second; ++it2)	{
				cout << it->first << " " << endl;
				cout << it2->second << " " << endl;
				cout << this->natvar[it2->second] << " " << endl;
				cout << this->natvar[it2->second]->index << " " << endl;
				cout << data_line[this->natvar[it2->second]->index]<< endl;
		}
			



		if(false)//data_line.size() != config[i].datas.size())// check if there is no blanks from the original header size
		{
			std::cout 	
			<< CONSOL_RED_TEXT  << "The line "
			<< CONSOL_CYAN_TEXT <<"xxx"
			<<CONSOL_RED_TEXT <<" has incorrect number of columns" 
			<< std::endl;
			exit(1);
		}
	}
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
			config.natvar.insert(pair<string, NatVariable*>(it->first+"::"+it2->first, it2->second));

		//Mapping the string name of datas to collection of vars datas name
		//=================================================================
		for( MetaName::iterator it2 = tmp_map.begin(); it2 != tmp_map.end(); ++it2)
			datatovar.insert(pair<string, string>(it->first, it->first+"::"+it2->first));

		//Cleaning the data_line to avoid conflicts:
		data_line.clear();
	}
	return ret;
}
