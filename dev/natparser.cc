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

static std::map<std::string, NatData*> str2natData;
static std::map<std::string, NatVariable*> str2natVariable;

NatConfig::NatConfig():datas(),variables(){}
NatData::NatData(){}
NatVariable::NatVariable(){}
NatExpression::NatExpression(){}

//Convert string into vector string
vector<string> natParse_str2vector(string read_line){

	vector<string> v;
	boost::char_separator<char> sep(" \t");
	boost::tokenizer<boost::char_separator<char>> tokens(read_line, sep);

	for (const auto& t : tokens){
		v.push_back(t);
	}

	return v;
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
//****************************************
//Parsing several configuration files YAML
//****************************************
bool natParseConfig(std::vector<NatConfig>& out,std::vector<std::string> configpath){
	for(int i=0;i<configpath.size();i++){
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

	//=======THIS IS A TEST=======
	cout<<conf.datas[0].name<<endl;
	cout<<conf.datas[1].name<<endl;
	//=============================
	return true;

}

//***************
//Update function
//***************
void NatData::update(){
	//TODO
	//read line and write to readline
}


//****************
//YAML operator >>
//****************
bool operator>>(const YAML::Node& node, std::vector<NatData>& datas){

	NatData data;//declared once here because push_back makes a copy
	string path;
	bool ret=true;


	for(size_t i=0 ; i< node.size(); i++){
	
		datas.push_back(data);

		//====================================
		node[i]["name"]>>datas.back().name;

		// if(str2natData[datas.back().name]!=NULL){
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

		if(! datas.back().file->is_open() ){
			cout
			<<CONSOL_RED_TEXT   <<"ERROR : (line"
			<<CONSOL_CYAN_TEXT  << 666
			<<CONSOL_RED_TEXT   <<") cannot open "
			<<CONSOL_CYAN_TEXT  <<path
			<<CONSOL_RED_TEXT   <<" !\n"
			<<CONSOL_NORMAL_TEXT;

			ret=false;
		}else{
			//TODO
			//READ HEADER
			vector<string> readLine;
			//var name
			if(!natParseNext(datas.back().file,datas.back().header_name))
				ret = false;
			//unit
			if(natParseNext(datas.back().file,datas.back().header_unit))
				ret = false;
			//error
			if(natParseNext(datas.back().file,datas.back().header_error))
				ret = false;
		}
		//====================================

		//map str2natData
		//equivalent to:
		//	str2natData[datas.back().name]=&( datas.back() );
		str2natData.insert( pair<string,NatData*>( datas.back().name , &( datas.back() ) ) );

	}
	return ret;
}





bool operator>>(const YAML::Node& node, std::vector<NatVariable>& vars){
	NatVariable var;
	string str;
	string str2;
	bool ret = true;
	for(size_t i=0 ; i< node.size(); i++){
		vars.push_back(var);

		//=========================================================
		//=========================================================
		// std::string name;
		node[i]["varname"]>>vars.back().name;
		if(str2natVariable.find(vars.back().name)!=str2natVariable.end()){
			cout
			<<CONSOL_RED_TEXT<<"ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") you cannot name two variables with the same name ("
			<<CONSOL_CYAN_TEXT<<vars.back().name
			<<CONSOL_RED_TEXT<<") !"
			<<endl<<CONSOL_NORMAL_TEXT;
			cout.flush();
			ret=false;
		}
		//map str2natVariable
		//equivalent to:
		//	str2natVariable[vars.back().name]=&( vars.back() );
		str2natVariable.insert( pair<string,NatVariable*>( vars.back().name , &( vars.back() ) ) );



		//=========================================================
		//=========================================================
		// NatData * data;
		node[i]["var"]>>str;
		size_t pos = str.find("::");
		str2 = str.substr (0,pos);

		if(pos==string::npos){
			cout
			<<CONSOL_RED_TEXT<<"ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") variable "
			<<CONSOL_CYAN_TEXT<<str
			<<CONSOL_RED_TEXT<<"\'s data missing (format should be myData::var)"<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;
		}else{
			vars.back().data = str2natData[str2];
			if(vars.back().data==NULL){
				cout
				<<CONSOL_RED_TEXT<<"ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") data "
				<<CONSOL_CYAN_TEXT<<str2
				<<CONSOL_RED_TEXT<<" does not exist !"<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;
			}
		}


		// Unit unit;
		try{
			node[i]["unit"]>>str;
			vars.back().unit= str2unit(str);
		}catch(YAML::TypedKeyNotFound<std::string> e){
			//TODO
			cout<<"TODO: get UNIT in data"<<endl;
			//vars.back().unit= str2unit(str);
		}

		// double value;
		// std::string value_str;
		vars.back().value_str;


		// - varname: Agent_X
		// var: myData1::var1
		// unit: UNITE
		// expr: Agent_W + Agent_Z
	}
	return ret;	
}


bool operator>>(const YAML::Node& node, std::vector<NatExpression>& vars){
	//TODO
	bool ret=true;
	for(size_t i=0 ; i< node.size(); i++){
	
		NatExpression var;
		//====================================
		node[i]["varname"]>>var.varname;
		//====================================
		const YAML::Node& expr_node = node[i]["expr"];
	 	for(unsigned j = 0; j < expr_node.size(); j++){

	 		expr_node[j] >> var.expr;
		}
		vars.push_back(var);
		cout << vars[i].varname << " " << vars[i].expr << std::endl;
	}
}

bool operator>>(const YAML::Node& node, std::vector<NatLateXt>& vars){
	
	bool ret=true;
	for(size_t i=0 ; i< node.size(); i++){
	
		NatLateXt var;
		//====================================
		node[i]["path"]>>var.path;
		//====================================
		const YAML::Node& content_node = node[i]["content"];
	 	for(unsigned j = 0; j < content_node.size(); j++){

			std::string content;
	 		content_node[j] >> content;
	 		var.contents.push_back(content);
		}
		vars.push_back(var);
	}
	return ret;
}


bool operator>>(const YAML::Node& node, NatConfig& config){
	bool ret=true;
	if(! (node["data"]>> config.datas))
		ret= false;
	//read all headers
	if(! (node["variables"] >> config.variables))
		ret= false;
	if(! (node["expressions"] >> config.expressions))
		ret= false;
	if(! (node["text"] >> config.text))
		ret= false;
	if(! (node["latex"] >> config.latex))
		ret= false;
	if(! (node["gnuplot"] >> config.gnuplot))
		ret= false;
	return ret;
}


/*

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
//signal if commentline !
bool natParseNext(ifstream& input_file,vector<string>& output){
	string read_line;

	while(output.size()==0 && input_file.good()){
		getline(input_file,read_line);
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


NatInfo::NatInfo():name(),unit(),error(),formula() {}


//TODO
//
//Complete missing things : calculate Unit
//check Units is formulae
//
//weird stuff like [[] or []]
//error in % or %0 or constant or variable
//check end with ]
//



vector<NatInfo> natParseHeader(vector<string> input){

	cout<<CONSOL_LIGHTGRAY_TEXT
	<<"! HEADER PARSE !"<<endl
	<<"^^^^^^^^^^^^^^^^"<<endl;

	vector<NatInfo> c;
	for(auto & t:input){
		NatInfo n;

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
		if(i<t.size() && t[i]=='['){
			i++;
			while(i<t.size() && t[i]!=']'){
				n.formula.push_back(t[i]);
				i++;
			}
		}

		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"read    : "<<CONSOL_CYAN_TEXT<<t<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"name    : "<<CONSOL_NORMAL_TEXT<<n.name<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"unit    : "<<CONSOL_NORMAL_TEXT<<n.unit<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"error   : "<<CONSOL_NORMAL_TEXT<<n.error<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"formula : "<<CONSOL_NORMAL_TEXT<<n.formula<<endl;
		cout<<CONSOL_LIGHTGRAY_TEXT<<"-->"<<"==================="<<endl;

		c.push_back(n);
	}

	cout<<CONSOL_LIGHTGRAY_TEXT
	<<"! HEADER PARSE !"<<CONSOL_MAGENTA_TEXT<<" --> DONE"<<endl;
	return c;
}



//using namespace boost;



//TODO
vector<double> natParseContent(vector<string> input){
	vector<double> ret;
	for(size_t i=0;i<input.size();i++){
		double d;
		try{
			d = boost::lexical_cast<double>(input[i]);
			ret.push_back(d);
		}catch (boost::bad_lexical_cast const&){
			//si ca ne marche pas,
			//c'est qu'il s'agit d'un
			//code...
			//NaN
			//to Calculate
		}
	}
	return ret;
}





*/
