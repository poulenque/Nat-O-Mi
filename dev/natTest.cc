#include "natTest.h"


void test_Parser(natOmi nato)
{
	for(size_t j(0);j < nato.conf.size();j++)
	{

		std::cout << "\nTESTING Parser:" << std::endl;
		//Print datas infos:
		std::cout << "\nDatas:" << std::endl;
		for(auto it =  nato.conf[j]->datas.cbegin(); it !=  nato.conf[j]->datas.cend(); ++it)
   		{	 std::cout << it->first << " " << it->second << std::endl;
		}

		//Print  variables:
		std::cout << "\nVariables:" << std::endl;
		for(auto it =  nato.conf[j]->natvar.cbegin(); it !=  nato.conf[j]->natvar.cend(); ++it)
   			 std::cout << "MetaName: "<< it->first 
					<< " Data: " << it->second->data
				 	<< " Var:" << it->second->var
					<< " Unit:" << it->second->unit
					<< " Error: " << it->second->error<<std::endl;


		//Print  Output:
		std::cout << "\nOutput:" << std::endl;
		std::cout << "\nText:" << std::endl;
		for(size_t i(0);i <   nato.conf[j]->text.size();i++){
			std::cout <<  nato.conf[j]->text[i].path << "\n";
			for(size_t k(0);k <   nato.conf[j]->text[i].contents.size();k++)
				std::cout <<  nato.conf[j]->text[i].contents[k] << std::endl;
		}

		std::cout << "\nLatex:" << std::endl;
		for(size_t i(0);i <   nato.conf[j]->latex.size();i++){
			std::cout <<  nato.conf[j]->latex[i].path << "\n";
			for(size_t k(0);k <   nato.conf[j]->latex[i].contents.size();k++)
				std::cout <<  nato.conf[j]->latex[i].contents[k] << std::endl;
		}

	}
}

void test_Working(natOmi nato)
{
	for(unsigned int i(0);i < nato.conf.size();i++)
	{
		std::cout << "\nTESTING Computing:" << std::endl;	

		//Print the Headers into the different kind of outputs		
		//===================================================
		nato.conf[i]->printText(HEAD);
		nato.conf[i]->printLaTeX(HEAD);

		//Update the value of the variables to compute or write into output
		while(updateVars(nato.conf[i]))
		{
			//Compute all exprs from Expressions vetor and their errors
			//=========================================================
			//TODO function for that? or put natConPute back in natconpute.cc
			for(MetaExpr::const_iterator it = nato.conf[i]->natexprs.begin(); it != nato.conf[i]->natexprs.end(); ++it)
			{
				nato.conf[i]->natvar[it->first]->value = it->second->natConPute(nato.conf[i]->natvar);
				nato.conf[i]->natvar[it->first]->error = it->second->natUncerError(nato.conf[i]->natvar);
			}
			
			//Print the line into the different kind of outputs		
			//=================================================
			nato.conf[i]->printText();
			nato.conf[i]->printLaTeX();

		}
		//Print end of LaTeX table
		//========================
		nato.conf[i]->printLaTeX(3);

		cout << "The end? RENOMMER LE PROJET: N@-O-Me !!!!!!" << endl;
	}
}
