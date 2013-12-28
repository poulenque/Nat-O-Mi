#include "test.h"

void test_Parser(std::vector<NatConfig> config)
{
	for(size_t j(0);j < config.size();j++){

		std::cout << "\n TESTING Parser:" << std::endl;
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
		std::cout << "\n TESTING Working:" << std::endl;
		std::cout << "GLA:" << std::endl;	

		//Print the Headers into the different kind of outputs		
		//===================================================
		config[i].printText(1);
		config[i].printLaTeX(1);

		//Update the value of the variables to compute or write into output
		while(config[i].updateVars())
		{
			//Compute all exprs from Expressions vetor
			//========================================
			//TODO function for that? or put natConPute back in natconpute.cc
			for(size_t j(0);j < config[i].natexprs.size(); j++)
				config[i].natexprs[j]->natConPute(config[i].traduc, config[i].natvar);
			
			//Print the line into the different kind of outputs		
			//=================================================
			config[i].printText();
			config[i].printLaTeX();
			config[i].printGNUplot();

		}	
		cout << "The end" << endl;

		/*parseNext;


		line.push_back(config.natvar[output_i.contents].var_value)

		output << vector<string> line*/

		





		//This doesnt write the corret header!!!! problem
		/*output_file << data_line << std::endl;

		while(natParseNext(input_file,data_line) && input_file.good())
		{

			if(data_line.size() != nheader)// check if there is no blanks from the original header size
			{
				std::cout 	<< CONSOL_RED_TEXT  << "The line "
							<< CONSOL_CYAN_TEXT <<"xxx"
							<<CONSOL_RED_TEXT <<" has incorrect number of columns" 
							<< std::endl;
				exit(1);
			}

			//TODO
			//==========================================================
			//==========================================================
			//==========================================================
			//mettre en forme
			//faire les calculs sur la ligne
			//vector<double> parsed = natParseContent(data_line);

			//TODO
			//calcules pour la colonne
			for(unsigned int i(0); i < data_info.size(); i++)
			{	
				if(!data_info[i].formula.empty())
				{
					GiNaC::ex result(natConPute(data_info[i].formula,data_line,dataName_str2num));

					//Keep the sme amount of column but computing the good values
					if (GiNaC::is_a<GiNaC::numeric>(result) && i < nheader)
						data_line[i] = double2str(GiNaC::ex_to<GiNaC::numeric>(result).to_double()); //STUPID ????

					//Append the column
					else if(i >= nheader)
						data_line.push_back(double2str(GiNaC::ex_to<GiNaC::numeric>(result).to_double())); //STUPID ????
				}
			}

			//TODO
			//ecrire dans output proprement
			output_file << data_line << std::endl;
			//==========================================================
			//==========================================================
			//==========================================================

		}
		input_file.close();
		output_file.close();*/
	}
}
