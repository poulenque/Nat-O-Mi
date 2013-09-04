#include "consol_color.h"
#include "natparser.h"

#include <iostream>
#include <string>
#include <sstream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>


const string commentSymbol = "#";

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


natInfo::natInfo():name(),unit(),error(),formula() {}


//TODO
//
//Complete missing things : calculate Unit
//check Units is formulae
//
//weird stuff like [[] or []]
//error in % or %0 or constant or variable
//check end with ]
//



vector<natInfo> natParseHeader(vector<string> input){

	cout<<CONSOL_LIGHTGRAY_TEXT
	<<"! HEADER PARSE !"<<endl
	<<"^^^^^^^^^^^^^^^^"<<endl;

	vector<natInfo> c;
	for(auto & t:input){
		natInfo n;

		size_t i=0;
		while(i<t.size() && t[i]!='['){
			n.name.push_back(t[i]);
			i++;
		}
		//=======================
		//=======================
		if(i>=t.size()){
			cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<CONSOL_RED_TEXT<<"OMG you can't be a physicist ! \""<<CONSOL_CYAN_TEXT<< n.name
			<<CONSOL_RED_TEXT<<"\"\'s"<<" Unit are missing !!! are you mad ?"<<endl;
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
			<<CONSOL_RED_TEXT<<"\"\'s"<<" error estimation is missing !!!"<<endl;
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
