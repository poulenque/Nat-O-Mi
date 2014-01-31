#include "natYAML.h"


//***********************
//YAML operator >> Config
//***********************
bool operator>>(const YAML::Node& node, NatConfig& config)
{
	bool ret=true;

	if(!(node["data"]>> config.datas))
		ret= false;

	if(!(node["variables"] >> config.natvar))
		ret= false;

	if(!(node["expressions"] >> config.natexprs))
		ret= false;

	if(node.FindValue("text")){
		if(!(node["text"] >> config.text))
			ret= false;
	}
	if(node.FindValue("latex")){
		if(!(node["latex"] >> config.latex))
			ret= false;
	}
	if(node.FindValue("gnuplot")){
		if(!(node["gnuplot"] >> config.gnuplot))
			ret= false;
	}	
	return ret;
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

		if(datas.find(name)!=datas.end())
		{
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
		datas.insert( pair<string, std::ifstream*>(name, file));
	}
	return ret;
}

//****************************
//YAML operator >> Expressions
//****************************
bool operator>>(const YAML::Node& node, MetaExpr& exprs)
{
	std::string name;
	std::string formula;
	size_t prec(NatExprPrec);
	bool ret=true;
	for(size_t i=0 ; i< node.size(); i++){

		//===================================
		node[i]["name"]>>name;
		//************* EXPRESSIONS *************
		//***************************************
		//===================================
		node[i]["expr"]>>formula;	

		//Look for any optionnal precision
		//================================
		if(const YAML::Node *precision = node[i].FindValue("prec"))
    		*precision >> prec;

		NatExpressions* natexpr = new NatExpressions(formula, prec);

		//Insert the new variable into the expr map
		//=========================================
		exprs.insert( pair<string, NatExpressions*>(name, natexpr));

	}
	return ret;
}

//*************************
//YAML operator >> Variable
//*************************
bool operator>>(const YAML::Node& node, MetaVar& vars){

	std::string str,data,var,name;
	size_t pos;
	bool ret = true;
	for(size_t i=0 ; i< node.size(); i++)
	{
		//Get Name
		//========
		node[i]["name"]>>name;

		//Checks if there is a redfinition of data vars which is stupid
		//=============================================================
		if(vars.find(name)!=vars.end())
		{
			cout
			<<CONSOL_RED_TEXT<<"ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") var "
			<<CONSOL_CYAN_TEXT<<name
			<<CONSOL_RED_TEXT<<" has been redifined"
			<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;//FAIRE DES EXIT(0) plus cool TODO
		}	
		//Get In
		//========
		node[i]["in"]>>str;
		pos = str.find("::");
		data = str.substr(0,pos);
		var = str.substr(pos+2);// avoid the "::"
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
			<<CONSOL_CYAN_TEXT<< name
			<<CONSOL_RED_TEXT<<"\'s data missing (format should be myData::var)"<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;
		}

		//Mapping the string name of meta name to corresponding var
		//=========================================================
		vars.insert(pair<string, NatVariable*> (name, new NatVariable(data,var,Unit(),""))); //TODO whoot
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
		}
		
		//Caption node for text, latex, etc...
		//====================================
		if(const YAML::Node *caption = node[i].FindValue("caption"))
    		*caption >> outs.back().caption;

		//Label node for text, latex, etc...
		//==================================
		if(const YAML::Node *label = node[i].FindValue("label"))
    		*label >> outs.back().label;
	}
	return ret;
}
