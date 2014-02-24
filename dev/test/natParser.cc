#include "natParser.h"

//***********************
//NATOMI HEADER PARSE
//***********************
//TODO  maybe put defines here or wait for YAML parsing sep
string natGetHeadings(const string& str, size_t& i, const char& c, const string& cc)
{
	string tmp;

   	while(str[i]!=c)
	{
    	if(cc.find(str[i])==string::npos) 
			tmp.push_back(str[i]);

		else
		{
			cerr << CONSOL_RED_TEXT << "Invalid header formatting!!!!::: " << CONSOL_NORMAL_TEXT << endl;//TODO
			exit(EXIT_FAILURE);
		}
     	i++;
   	}
	i++;
	return tmp;
}

bool natParseHeader(NatConfig& config)
{
	//Parsing Header Files of datas en then mapping variables
	//*******************************************************
	if(config.debug)
    	cout<<CONSOL_LIGHTGRAY_TEXT
    	<<"! HEADER PARSE !"<<endl
    	<<"^^^^^^^^^^^^^^^^"<<endl;

	//Guess that we use all vars from config & exprs
	//**********************************************
	MetaVar tmp_vars(config.natvar.size()+config.natexprs.size());

	//Looping thru all the datas of config and do the parsing
	//*******************************************************
	bool ret(true);
	for(NatData::iterator it = config.datas.begin(); it != config.datas.end(); ++it)
	{
		long long int index(0);
		ifstream file(it->second.path);
		file.seekg(0, std::ios::end);
		size_t size = file.tellg();
		it->second.buffer = string(size, ' ');
		file.seekg(0);
		file.read(&(it->second.buffer[0]), size); //TODO buffer only a part of file
		//Next line just clear following empty lines
		skipBlanks(it->second.buffer,it->second.pointer);

    	while(it->second.buffer[it->second.pointer]!='\n')
		{
			NatVariable* n = new NatVariable();

			n->var=natGetHeadings(it->second.buffer, it->second.pointer,'[',"]\n#\r");//TODO comment symbol
			n->unit = str2unit(natGetHeadings(it->second.buffer, it->second.pointer,']',"[\n#\r"));
	
			//We don't want anything between units and errors
			if(natGetHeadings(it->second.buffer, it->second.pointer,'[',"]\n#\r").size()!=0)
			{
				cerr << CONSOL_RED_TEXT << "Invalid space between " 
					<< n->var << "[" << n->unit 
					<< CONSOL_CYAN_TEXT << "]" << CONSOL_CYAN_BG << "  " 
					<< CONSOL_NORMAL_BG+CONSOL_CYAN_TEXT << "[" << CONSOL_RED_TEXT 
					<< n->error << "]!"
					<< CONSOL_NORMAL_TEXT << endl;
				exit(EXIT_FAILURE);
			}

   			n->error=natGetHeadings(it->second.buffer, it->second.pointer, ']',"[#");
			n->data = it->first;
			n->index = index;
			index++;

			//TODO  maybe put defines here or wait for YAML parsing sep
			//Skip the separator:
			while(string(" \t").find(it->second.buffer[it->second.pointer])!=string::npos)
				it->second.pointer++;
			
			if(config.debug){
			//==================================================================================
			cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"name : "<<CONSOL_BLUE_TEXT<<n->var<<endl;
			cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"unit : "<<CONSOL_BLUE_TEXT<<n->unit<<endl;
			cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"error : "<<CONSOL_BLUE_TEXT<<n->error<<endl;
			cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"index : "<<CONSOL_BLUE_TEXT<<n->index<<endl;
			cout<<CONSOL_LIGHTGRAY_TEXT<<"--> "<<"data : "<<CONSOL_BLUE_TEXT<<n->data<<endl;
			cout<<CONSOL_LIGHTGRAY_TEXT<<"-->"<<"==================="<<endl;}


			//We update the new information into the has map of vars in data
			//**************************************************************
 			it->second.vars.insert( pair<long long int,NatVariable*>( n->index , n));

			//Updating the Vars has map from config & check if var exists in data
			//*******************************************************************
			MetaVar::iterator pos=config.natvar.find(it->first+n->var);
			if(pos!=config.natvar.end())
				tmp_vars.insert( pair<string,NatVariable*>(pos->second->var,n));


			/*else
			{
				cout
				<<CONSOL_RED_TEXT<<"VARIABLE ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") var "
				//<<CONSOL_CYAN_TEXT<< pos->second->var TODO impossible acces to pos if it equal to natvar.end()
				<<CONSOL_RED_TEXT<<" does not exist, in data:"
				<<CONSOL_CYAN_TEXT<< it->first
				<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;
			}*/


 		}//End of While

		//We swap tmp vars and config vars to update config vars
		//******************************************************
		swap(tmp_vars,config.natvar);


		if(config.debug)
			cout<<CONSOL_LIGHTGRAY_TEXT <<"! HEADER PARSE !"
				<<CONSOL_MAGENTA_TEXT<<" --> DONE"
				<< CONSOL_NORMAL_TEXT << endl;

	}
    return ret;
}
