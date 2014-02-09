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

	if(node.FindValue("expressions")){
		if(!(node["expressions"] >> config.natexprs))
			ret= false;
	}

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
//YAML operator >> Data TODO OPTIMISER EN SUPPOSANT LA TAILLE DES MAPS!!! commencer par expr c'est plus simple
//*********************
bool operator>>(const YAML::Node& node, NatData& datas){

	bool ret=true;
	string path;
	std::string name;

	for(size_t i=0 ; i< node.size(); i++){

		//====================================
		node[i]["name"]>>name;

		if(datas.find(name)!=datas.end())
		{
			cout
			<<CONSOL_RED_TEXT   <<"DATA ERROR : (line"
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
		ifstream input;
		try{
           input.exceptions(ofstream::failbit | ofstream::badbit);
           input.open(path, ios_base::app);
           input.exceptions(ofstream::goodbit);
        }
        catch(ofstream::failure const &ex){
			cout << CONSOL_RED_TEXT << SOFT_NAME << SOFT_VERSION << " error while opening file: " << CONSOL_CYAN_TEXT << path << CONSOL_NORMAL_TEXT << endl;
            cout << CONSOL_RED_TEXT << ex.what() << endl;
			exit(EXIT_FAILURE);
		}
		datas.insert( pair<string, Data>(name, Data(path)));
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
			<<CONSOL_RED_TEXT<<"VARIABLE ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") var "
			<<CONSOL_CYAN_TEXT<<name
			<<CONSOL_RED_TEXT<<" has been redifined"
			<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;
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
			<<CONSOL_RED_TEXT<<"VARIABLE ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") variable "
			<<CONSOL_CYAN_TEXT<< name
			<<CONSOL_RED_TEXT<<"\'s data missing (format should be myData::var)"<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;
		}

		//Mapping the string name of meta name to corresponding var
		//=========================================================
		vars.insert(pair<string, NatVariable*> (data+var, new NatVariable(data,name,Unit(),DEFAULT_STRING)));
	}
	return ret;	
}

//************************
//YAML operator >> Outputs
//************************
bool operator>>(const YAML::Node& node, std::vector<NatOutPute>& outs){
	
	NatOutPute out;
	string path;
	bool ret=true;
	for(size_t i=0 ; i< node.size(); i++){

		//===================================
		outs.push_back(out);
		//====================================
		node[i]["path"]>>path;
		ofstream output;

		try{
           output.exceptions(ofstream::failbit | ofstream::badbit);
           output.open(path);
           output.exceptions(ofstream::goodbit);
        }
        catch(ofstream::failure const &ex){
			cout << CONSOL_RED_TEXT << SOFT_NAME << SOFT_VERSION << " error while opening file: " << CONSOL_CYAN_TEXT << path << CONSOL_NORMAL_TEXT << endl;
            cout << CONSOL_RED_TEXT << ex.what() << endl;
			exit(EXIT_FAILURE);
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

		//Separator node for text TODO  polymorphisme or whatever so you cannot use sep with latex
		//=======================
		if(const YAML::Node *sep = node[i].FindValue("separator"))
    		*sep >> outs.back().sep;
	}
	return ret;
}
