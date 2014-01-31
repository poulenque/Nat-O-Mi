#include "natConfig.h"

//***************************************
//Function to check what have been parsed
//***************************************
bool NatConfig::checkVars()
{
	bool ret(true);

	for(MetaVar::iterator it = this->natvar.begin(); it != this->natvar.end(); ++it )
	{//TODO check to not loop through all the vars
		//Checks if data exist
		//====================
		if(this->datas.find(it->second->data)==this->datas.end())
		{
			cout
			<<CONSOL_RED_TEXT<<"ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") data "
			<<CONSOL_CYAN_TEXT<< it->second->data
			<<CONSOL_RED_TEXT<<" does not exist!"<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;
		}
		//Check if the variable exists in data
		//====================================
		MetaVar::iterator pos = this->natvar.find(it->second->data+"::"+it->second->var);
		if(pos==this->natvar.end())
		{
			cout
			<<CONSOL_RED_TEXT<<"ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") var "
			<<CONSOL_CYAN_TEXT<< it->second->var
			<<CONSOL_RED_TEXT<<" does not exist, in data:"
			<<CONSOL_CYAN_TEXT<< it->second->data
			<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;//FAIRE DES EXIT(0) plus cool TODO
		}
		//Mapping the string name of meta var to corresponding real var from data
		//=======================================================================
		else if(it->first.find("::")==string::npos)//TODO ugly might disappear with optimization, or define it!
		{
			this->natvar.erase(pos);
			this->natvar.erase(it);
			delete it->second;//erase doesnt delete deeply 
			//we need to delete the temp NatVar build from
			//YAML parsing
			//pos->first=it->second->var;
			this->natvar.insert( pair<string, NatVariable*> (it->first,pos->second));
		}	
	}
	return ret;
}

bool NatConfig::checkExpr()
{
	bool ret(true);

	//TODO ALGORYTHM, apply the expression error also :)
	MetaExpr map;
	for(MetaExpr::iterator it = this->natexprs.begin();it != this->natexprs.end(); ++it)
	{
		//Mapping the string name of meta var to corresponding var /\ error
		//=================================================================
		this->natvar.insert( pair<string, NatVariable*> (it->first, new NatVariable("N/A",it->first,Unit(),it->first+NatErrorSuffix)));
		this->natvar.insert( pair<string, NatVariable*> (it->first+NatErrorSuffix, new NatVariable("N/A", it->first+NatErrorSuffix,Unit(),"N/A")));//TODO N/A TO BE DEFINED


		//Look if all the vars has been declared previously
		//=================================================
		for(GiNaC::symtab::iterator it2 = it->second->table.begin();
			it2 != it->second->table.end(); ++it2)
		{
			if(this->natvar.find(it2->first)==this->natvar.end())//FAIRE UNE FONCTION TEST TODO
			{	
				cout
				<<CONSOL_RED_TEXT<<"ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") MetaVar "
				<<CONSOL_CYAN_TEXT<< it2->first
				<<CONSOL_RED_TEXT<<" does not exist"
				<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;//FAIRE DES EXIT(0) plus cool TODO
			}
		}
		//Implementation of the error formula associate to the new var from expr
		//======================================================================
		map.insert(pair<string, NatExpressions*>(it->first+NatErrorSuffix, new NatExpressions(it->second->natUncerError(this->natvar), it->second->prec)));
	}

	//Insert the new errors expr from map into the Config expr map
	//============================================================
	this->natexprs.insert(map.begin(), map.end());

	return ret;
}


bool NatConfig::checkOutput()//TODO repition see about merging all the kind of outputs
{
	bool ret(true);
	for(size_t i(0);i < this->text.size();i++)
	{
		for(size_t j(0);j < this->text[i].contents.size();j++)
		{
			if(this->natvar.find(this->text[i].contents[j])==this->natvar.end())//FAIRE UNE FONCTION TEST TODO
			{	
				cout
				<<CONSOL_RED_TEXT<<"ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") Natvar "
				<<CONSOL_CYAN_TEXT<< this->text[i].contents[j]
				<<CONSOL_RED_TEXT<<" does not exist"
				<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;//FAIRE DES EXIT(0) plus cool TODO
			}
		}
	}


	for(size_t i(0);i < this->latex.size();i++)
	{
		for(size_t j(0);j < this->latex[i].contents.size();j++)
		{
			if(this->natvar.find(this->latex[i].contents[j])==this->natvar.end())//FAIRE UNE FONCTION TEST TODO
			{	
				cout
				<<CONSOL_RED_TEXT<<"ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") Natvar "
				<<CONSOL_CYAN_TEXT<< this->latex[i].contents[j]
				<<CONSOL_RED_TEXT<<" does not exist"
				<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;//FAIRE DES EXIT(0) plus cool TODO
			}
		}
	}
	return ret;
}

//*************************** //TODO TODO TODO TODO EASY
//NatConfig printings methods //TODO do a natOutput.cc file for these methods?? and build a class?
//***************************
void NatConfig::printText(bool NatHeader)
{
	for(size_t j(0);j <  this->text.size();j++)
	{
		//Opening the outputfile //TODO check for errors in opening for ret value
		std::ofstream output(this->text[j].path, ios_base::app);
	
		//Only the first time, writing the heading files
		if(NatHeader)
		{
			for(size_t k(0);k <  this->text[j].contents.size();k++)
				output << *this->natvar[this->text[j].contents[k]] << " " ;
		}
		else
		{	for(size_t k(0);k <  this->text[j].contents.size();k++)
				output << this->natvar[this->text[j].contents[k]]->value << " 	" ;//TODO ASK FOR SEPERATOR
		}
		
		output << std::endl;
		output.close();
	}
}

//TODO,NB: GiNaC allows to print in latex format
//Could be cool!

//TODO BWERK GO PUT THIS IN A CLASS!
void NatConfig::printLaTeX(size_t NatHeader)
{
	for(size_t j(0);j < this->latex.size();j++)
	{
		//Opening the outputfile //TODO check for errors in opening for ret value
		std::ofstream output(this->latex[j].path, ios_base::app);

 		switch(NatHeader)
		{
	
			case HEAD:
			{
				output << "%This file is generated with N@-O-Mi-3.0" << std::endl;//Beurk?

				output << "\\begin{table}[h]" << std::endl;
				output << "\t\\caption{"<< this->latex[j].caption << "}" << "\\label{tab:" << this->latex[j].label << "}" << std::endl;
				output << "\t\t\\begin{tabular}{";
				for(unsigned int k(0);k < this->latex[j].contents.size();output << "|l",k++);
				output << "|}" << std::endl;
				output << "\t\t\\hline" << std::endl;//tab maybe

				output << "\t\t";
				unsigned int end(this->latex[j].contents.size()-1);//TODO to a << operator with LaTeX support 
				for(unsigned int k(0);k < this->latex[j].contents.size()-1;output << this->natvar[this->latex[j].contents[k]]->var << " & ",k++);
				output << this->natvar[this->latex[j].contents[end]]->var << "\\\\" << " \\hline"<< std::endl;
				break;
			}
		
			case MIDDLE:
			{
				output << "\t\t";
				unsigned int end(this->latex[j].contents.size()-1);
				for(unsigned int k(0);k < this->latex[j].contents.size()-1;output << this->natvar[this->latex[j].contents[k]]->value << " & ",k++);
				output << this->natvar[this->latex[j].contents[end]]->value << "\\\\" << " \\hline"<< std::endl;
				break;
			}

			case END:
			{
				output << "\t\t\\hline" << std::endl;
				output << "\t\\end{tabular}" << std::endl;
				output << "\\end{table}" << std::endl;
				break;
			}

			default:
				std::cout << "Invalid Latex parameter" << std::endl;
		}
		output.close();
		}
}
