#include "natConfig.h"

//*************************
//Constructor && Destructor
//*************************
NatConfig::NatConfig(bool d):debug(d){}
NatConfig::~NatConfig(){}

//***************************************
//Function to check what have been parsed
//***************************************
bool NatConfig::checkVars()
{
	bool ret(true);
	MetaVar tmp_map;
	for(MetaVar::iterator it = this->natvar.begin(); it != this->natvar.end(); ++it )
	{
		//Checks if data exist
		//====================
		if(this->datas.find(it->second->data)==this->datas.end())
		{
			cout
			<<CONSOL_RED_TEXT<<"VARIABLE ERROR : (line"
			<<CONSOL_CYAN_TEXT<< 666
			<<CONSOL_RED_TEXT<<") data "
			<<CONSOL_CYAN_TEXT<< it->second->data
			<<CONSOL_RED_TEXT<<" does not exist!"<<endl<<CONSOL_NORMAL_TEXT;
			ret=false;
		}
	}
	return ret;
}

bool NatConfig::checkExpr()
{
	bool ret(true);

	MetaExpr map(this->natexprs.size());
	for(MetaExpr::iterator it = this->natexprs.begin();it != this->natexprs.end(); ++it)
	{
		//Mapping the string name of meta var to corresponding var /\ error
		//=================================================================
		this->natvar.insert( pair<string, NatVariable*> (it->first, new NatVariable(DEFAULT_STRING,it->first,Unit(),it->first+NatErrorSuffix)));
		this->natvar.insert( pair<string, NatVariable*> (it->first+NatErrorSuffix, new NatVariable(DEFAULT_STRING, it->first+NatErrorSuffix,Unit(),DEFAULT_STRING)));


		//Look if all the vars has been declared previously
		//=================================================
		for(GiNaC::symtab::iterator it2 = it->second->table.begin();
			it2 != it->second->table.end(); ++it2)
		{

			if(this->natvar.find(it2->first)==this->natvar.end())
			{	
				cout
				<<CONSOL_RED_TEXT<<"EXPRESSION ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") MetaVar "
				<<CONSOL_CYAN_TEXT<< it2->first
				<<CONSOL_RED_TEXT<<" does not exist"
				<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;
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


bool NatConfig::checkOutput()
{
	bool ret(true);
	for(size_t i(0);i < this->text.size();i++)
	{
		for(size_t j(0);j < this->text[i].contents.size();j++)
		{
			if(this->natvar.find(this->text[i].contents[j])==this->natvar.end())
			{	
				cout
				<<CONSOL_RED_TEXT<<"OUTPUT TEXT ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") Natvar "
				<<CONSOL_CYAN_TEXT<< this->text[i].contents[j]
				<<CONSOL_RED_TEXT<<" does not exist"
				<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;
			}
		}
	}


	for(size_t i(0);i < this->latex.size();i++)
	{
		for(size_t j(0);j < this->latex[i].contents.size();j++)
		{
			if(this->natvar.find(this->latex[i].contents[j])==this->natvar.end())
			{	
				cout
				<<CONSOL_RED_TEXT<<"OUTPUT LATEX ERROR : (line"
				<<CONSOL_CYAN_TEXT<< 666
				<<CONSOL_RED_TEXT<<") Natvar "
				<<CONSOL_CYAN_TEXT<< this->latex[i].contents[j]
				<<CONSOL_RED_TEXT<<" does not exist"
				<<endl<<CONSOL_NORMAL_TEXT;
				ret=false;
			}
		}
	}
	return ret;
}

//****************************************************
//NatConfig Computing Vars and Errors from Expr tables
//****************************************************
void NatConfig::computeVars()
{
	for(MetaExpr::const_iterator it = this->natexprs.begin(); it != this->natexprs.end(); ++it)
	{
		this->natvar[it->first]->value = it->second->natConPute(this->natvar);
		//this->natvar[it->first]->error = it->second->natUncerError(this->natvar);
	}
}

//***************************TODO OPTIMISER LE OUTPUT
//NatConfig printings methods
//***************************
void NatConfig::printText(bool NatHeader)
{
	for(size_t j(0);j <  this->text.size();j++)
	{
		std::ofstream output(this->text[j].path, ios_base::app);
	
		//Only the first time, writing the heading files
		if(NatHeader)
		{
			for(size_t k(0);k <  this->text[j].contents.size();k++)
				output << *this->natvar[this->text[j].contents[k]] << this->text[j].sep;
		}
		else
		{	for(size_t k(0);k <  this->text[j].contents.size();k++)
				output << this->natvar[this->text[j].contents[k]]->value << this->text[j].sep;
		}
		
		output << std::endl;
		output.close();
	}
}

//TODO,NB: GiNaC allows to print in latex format
//Could be cool!
void NatConfig::printLaTeX(size_t NatHeader)
{
	for(size_t j(0);j < this->latex.size();j++)
	{
		std::ofstream output(this->latex[j].path, ios_base::app);

 		switch(NatHeader)
		{
	
			case HEAD:
			{
				output << "%This file is generated with "<< SOFT_NAME << SOFT_VERSION << std::endl;

				output << "\\begin{table}[h]" << std::endl;
				output << "\t\\caption{"<< this->latex[j].caption << "}" << "\\label{tab:" << this->latex[j].label << "}" << std::endl;
				output << "\t\t\\begin{tabular}{";
				for(unsigned int k(0);k < this->latex[j].contents.size();output << "|l",k++);
				output << "|}" << std::endl;
				output << "\t\t\\hline" << std::endl;//tab maybe

				output << "\t\t";
				unsigned int end(this->latex[j].contents.size()-1);
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
