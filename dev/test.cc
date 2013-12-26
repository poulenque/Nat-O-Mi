#include "test.h"

void test_Parser(std::vector<NatConfig> config)
{
	for(size_t j(0);j < config.size();j++){

		//Print datas infos:
		std::cout << "\nDatas:" << std::endl;
		for(size_t i(0);i <  config[j].datas.size();i++)
			std::cout << config[j].datas[i].name << "\n" <<  config[j].datas[i].file << std::endl;

		//Print  variables:
		std::cout << "\nVariables:" << std::endl;
		for(auto it = config[j].natvar.cbegin(); it != config[j].natvar.cend(); ++it)
   			 std::cout << it->first << "\n";


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
