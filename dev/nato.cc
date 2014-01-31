#include "nato.h"

//***********************
//Config update vars Func
//***********************
bool updateVars(NatConfig* conf)
{
	std::vector<std::string> data_line;
	//update var_value;//global so there is no mistakes
	//=================================================
	for(NatData::iterator it = conf->datas.begin(); it != conf->datas.end(); ++it)
	{
		if(!natParseNext(it->second,data_line))
			return false;

		//Check if there is the good number of columns
		//============================================
		size_t varcount(0);
		for(MetaVar::iterator it2 = conf->natvar.begin(); data_line.size()<=varcount, it2 != conf->natvar.end();it2++)
		{
			if(it2->second->data==it->first)
			{
				it2->second->value = str2double(data_line[it2->second->index]);
				varcount++;
			}
		}
		
		//Check if there is the good number of columns
		//============================================
		if(data_line.size()!=varcount)
		{
			std::cout 	
			<<CONSOL_RED_TEXT<< "The line "
			<<CONSOL_CYAN_TEXT<<"xxx"
			<<CONSOL_RED_TEXT<<" has incorrect number of columns" 
			<<std::endl;
			return false;
		}
			
		//Cleaning the data_line to avoid conflicts:
		data_line.clear();
	}
	return true;
}
