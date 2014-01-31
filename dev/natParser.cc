#include "natParser.h"

const string commentSymbol = "#";//TODO put as define

using namespace std;

//****************************************
//Parsing several configuration files YAML
//****************************************
bool natParseConfig(std::vector<NatConfig*>& out,std::vector<std::string> configpath){
	for(size_t i=0;i<configpath.size();i++){
		NatConfig* conf = new NatConfig();
		if(!natParseConfig(*conf,configpath[i]))
			return false;
		out.push_back(conf);
	}
	return true;
}

//**************************************
//Parsing unique configuration file YAML
//**************************************

bool natParseConfig(NatConfig& conf, std::string configpath)
{
	bool ret(true);

	std::ifstream read(configpath);

	if(!read.is_open()){
		cout<<CONSOL_RED_TEXT<<"could not open file "<<CONSOL_CYAN_TEXT<<configpath<< endl;
		ret = false;
	}

	//YAML Parsing
	//************
	YAML::Parser parser(read);
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

	if(!conf.checkOutput())
		ret = false;

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
MetaVar natParseHeader(vector<std::string> input){

        cout<<CONSOL_LIGHTGRAY_TEXT
        <<"! HEADER PARSE !"<<endl
        <<"^^^^^^^^^^^^^^^^"<<endl;

        MetaVar varmap;
        size_t index(0);
        for(auto & t:input){
        	NatVariable* n = new NatVariable();

                size_t i=0;
                while(i<t.size() && t[i]!='['){
                        n->var.push_back(t[i]);
                        i++;
                }
                //=======================
                //=======================
                if(i>=t.size()){
                        cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<CONSOL_RED_TEXT<<"OMG you can't be a physicist ! \""<<CONSOL_CYAN_TEXT<< n->var
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
                        cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<CONSOL_RED_TEXT<<"No error ?! Are you kidding me ?\""<<CONSOL_CYAN_TEXT<< n->var
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
                cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"read : "<<CONSOL_CYAN_TEXT<<t<<endl;
                cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"name : "<<CONSOL_NORMAL_TEXT<<n->var<<endl;
                cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"unit : "<<CONSOL_NORMAL_TEXT<<n->unit<<endl;
                cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"error : "<<CONSOL_NORMAL_TEXT<<n->error<<endl;
                cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"index : "<<CONSOL_NORMAL_TEXT<<n->index<<endl;
                cout<<CONSOL_LIGHTGRAY_TEXT<<"-->"<<"==================="<<endl;

                //===========================================================
                varmap.insert( pair<std::string,NatVariable*>( n->var , n));
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

bool natParseHeader(NatConfig& config)//TODO optimization??
{
	bool ret=true;
	std::vector<std::string> data_line;

	for(NatData::iterator it = config.datas.begin(); it != config.datas.end(); ++it )
	{
		//trouver la ligne avec les noms de variable
		if(!natParseNext(it->second,data_line)){
			cout<<CONSOL_RED_TEXT<<"\""<<CONSOL_CYAN_TEXT<<*it->second
			<<CONSOL_RED_TEXT<<"\" is empty."<<endl;
			ret=false;
		}

		//Parsing Header Files of datas en then mapping variables
		//=======================================================
		MetaVar tmp_map = natParseHeader(data_line);
		for(MetaVar::iterator it2 = tmp_map.begin(); it2 != tmp_map.end(); ++it2 )
		{
			it2->second->data=it->first;
			config.natvar.insert(pair<string, NatVariable*>(it->first+"::"+it2->first, it2->second));
		}

		//Cleaning the data_line to avoid conflicts:
		data_line.clear();
	}
	return ret;
}
