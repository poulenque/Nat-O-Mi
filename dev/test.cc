#include "test.h"

void test_Parser(std::vector<NatConfig> config)
{
	for(size_t j(0);j < config.size();j++){

		std::cout << "\nTESTING Parser:" << std::endl;
		//Print datas infos:
		std::cout << "\nDatas:" << std::endl;
		for(auto it = config[j].datas.cbegin(); it != config[j].datas.cend(); ++it)
   			 std::cout << it->first << " " << it->second <<"\n";

		//Print  variables:
		std::cout << "\nVariables:" << std::endl;
		for(auto it = config[j].natvar.cbegin(); it != config[j].natvar.cend(); ++it)
   			 std::cout << it->first << " " << it->second->name <<"\n";


		//Print  Output:
		std::cout << "\nOutput:" << std::endl;
		std::cout << "\nText:" << std::endl;
		for(size_t i(0);i <  config[j].text.size();i++){
			std::cout << config[j].text[i].path << "\n";
			for(size_t k(0);k <  config[j].text[i].contents.size();k++)
				std::cout << config[j].text[i].contents[k] << std::endl;
		}

		std::cout << "\nLatex:" << std::endl;
		for(size_t i(0);i <  config[j].latex.size();i++){
			std::cout << config[j].latex[i].path << "\n";
			for(size_t k(0);k <  config[j].latex[i].contents.size();k++)
				std::cout << config[j].latex[i].contents[k] << std::endl;
		}

		std::cout << "\nGnuPlot:" << std::endl;
		for(size_t i(0);i <  config[j].gnuplot.size();i++){
			std::cout << config[j].gnuplot[i].path << "\n";
			for(size_t k(0);k <  config[j].gnuplot[i].contents.size();k++)
				std::cout << config[j].gnuplot[i].contents[k] << std::endl;
		}

	}
}

void test_Working(std::vector<NatConfig> config)
{
	for(size_t i(0);i < config.size();i++)
	{
		std::cout << "\nTESTING Working:" << std::endl;
		std::cout << "GLA:" << std::endl;	

		//Print the Headers into the different kind of outputs		
		//===================================================
		config[i].printText(1);
		config[i].printLaTeX(1);

		//Update the value of the variables to compute or write into output
		while(config[i].updateVars())
		{
			//Compute all exprs from Expressions vetor and their errors
			//=========================================================
			//TODO function for that? or put natConPute back in natconpute.cc
			for(MetaExpr::const_iterator it = config[i].natexprs.begin(); it != config[i].natexprs.end(); ++it)
			{
				/*TO BE REMOVED TODO */
				std::ostringstream s;//TODO THIS IS TMP HAVE TO SWITCH TO DOUBLE VALUES
				s << it->second->natConPute(config[i].traduc, config[i].natvar);
				config[i].natvar[it->first]->value = s.str();//TODO CHECK at natparser.h NatVariable::value
				/*TO BE REMOVED TODO */

				config[i].natvar[it->first]->error = it->second->natUncerError(config[i].traduc, config[i].natvar);
			}
			
			//Print the line into the different kind of outputs		
			//=================================================
			config[i].printText();
			config[i].printLaTeX();
			config[i].printGNUplot();

		}
		//Print end of LaTeX table
		//========================
		config[i].printLaTeX(3);

		cout << "The end? RENOMMER LE PROJET: N@-O-Me !!!!!!" << endl;

	}
}
