#include "natparser.h"

#include <iostream>
#include <string>
#include <sstream>
#include <boost/tokenizer.hpp>

using namespace boost;

vector<string> natParseStr(string read_line){

	vector<string> v;

	char_separator<char> sep(" \t");
	tokenizer<char_separator<char>> tokens(read_line, sep);
	for (const auto& t : tokens){
		if(t[0]=='[')
			v[v.size()-1]+=t;
		else
			v.push_back(t);
	}

	return v;
}



vector<string> natParseNext(ifstream& input_file){
	vector<string> output;
	string read_line;

	while(output.size()==0 && input_file.good()){
		getline(input_file,read_line);
		output = natParseStr(read_line);
	}

	return output;
}



vector<natInfo> natParseHeader(vector<string> input){
	vector<natInfo> c;
	for(auto & t:input){
		natInfo n;

		size_t i=0;
		while(i<t.size() && t[i]!='['){
			n.name.push_back(t[i]);
			i++;
		}
		if(i>=t.size()){
			cout<<"OMG you can't be a physicist ! Unit are missing !!! are you mad ?"<<endl;
			exit(0);
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
		cout<<t<<endl;
		cout<<n.name<<endl;
		cout<<n.unit<<endl;
		// cout<<str2unit(n.unit);
		cout<<n.error<<endl;
		cout<<n.formula<<endl;
		cout<<"========="<<endl;

		c.push_back(n);
	}
	return c;
}


