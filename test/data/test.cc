#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h> 
#include <string>

using namespace std;

#define MAX_CONFIG 1
#define MAX_FILE 1
#define MAX_OUTPUT 10
#define MAX_VAR 40
#define MAX_LINE 40
#define MAX_EXPR 1
#define PREC 5


int main()
{

	/* initialize random seed: */
 	srand (time(NULL));

	ofstream myfile,config;
	string name,conf,VAR("Var"),data,var,NEWVAR("new_Var"),EXPR;

	cout <<"Software to test FFN " << endl;


	for(unsigned int k(0); k < MAX_FILE;k++)
	{

		name=to_string(k);
		name="data"+name;
		myfile.open(name.c_str());

		cout << "Writing Headers for " << MAX_VAR << " columns." << endl;
		for(unsigned int i(0);i < MAX_VAR-1;i++)
		{
			//VarX[Unit][Error]
			myfile << VAR << i <<"[s]"<< "[" <<  (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX))) << "]" << "\t";
		}	
			myfile << VAR << MAX_VAR-1 <<"[s]"<< "[" <<  (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX))) << "]" << endl;

		cout << "Writing contents for " << MAX_LINE << " lines." << endl;
		for(unsigned int i(0);i < MAX_LINE;i++)
		{
			for(unsigned int j(0);j < MAX_VAR-1;j++)
			{
				
				myfile <<  (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX))) << "\t";
			}
			myfile <<  (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX))) << endl;
		}

		 myfile.close();
	}

	//**********************
	//CONFIG PART GENERATING
	//**********************
	for(unsigned int k(0);k < MAX_CONFIG;k++)
	{
		conf=to_string(k);
		conf="in"+conf+".yaml";
		config.open(conf.c_str());

		cout << "Getting all data names for config" << endl;
		
		config << "data:\n";
		for(unsigned int i(0); i < MAX_FILE;i++)
		{
			data=to_string(i);
			data="data"+data;
			config << " - name: " << data << "\n" << "   path: " << data << endl;
		}

		cout << "Getting all var names for config" << endl;

		config << "variables:\n";
		for(unsigned int i(0); i < MAX_FILE;i++)
		{
			data=to_string(i);
			data="data"+data;
			for(unsigned int j(0); j < MAX_VAR;j++)
			{
				var=to_string(j);
				var=VAR+var;
				config << " - name: " << data << "_" << var << "\n" << "   in: " << data << "::" << var << endl;
			}
		}

		cout << "Getting all expr names for config" << endl;

		config << "expressions:\n";
		for(unsigned int i(0);i<MAX_EXPR;i++)
		{
			for(unsigned int j(0); j < MAX_FILE;j++)
			{
				data=to_string(j);
				data="data"+data;
				for(unsigned int t(1); t <= MAX_VAR-1;t++)
				{
					EXPR+="cos("+data+"_"+VAR+to_string(t)+")*";
				}
			}
			EXPR+="("+data+"_"+VAR+to_string(MAX_VAR-1)+")";
			var=to_string(i);
			var=NEWVAR+var;
			config << " - name: " << var << "\n" << "   expr: " << EXPR << "\n   prec: " << PREC << endl;
			EXPR="";//just in case of bug
		}
		
		cout << "Writing the text output for config" << endl;

		config << "text:\n";
		for(unsigned int i(0);i<MAX_OUTPUT;i++)
		{
			data=to_string(i);
			data="new_data"+data;
			config << " - path: " << data << endl;
 			config << "   content: [";
			for(unsigned int j(0); j < MAX_FILE;j++)
			{
				data=to_string(j);
				data="data"+data;
				for(unsigned int t(0); t < MAX_VAR;t++)
				{
					var=to_string(t);
					var=VAR+var;
					config <<  data << "_" << var << ",";
				}
				for(unsigned int t(0);t<MAX_EXPR-1;t++)
				{
					var=to_string(t);
					var=NEWVAR+var;
					config <<  var << "," << var+"_error,";
				}
			}
			var=to_string(MAX_EXPR-1);
			var=NEWVAR+var;
			config <<  var << "," << var+"_error" << "]" << endl;
			//var=VAR+var;
			//config <<  data << "_" << var << "]" << endl;
		}

		cout << "Writing the latex output for config" << endl;

		config << "latex:\n";
		for(unsigned int i(0);i<MAX_OUTPUT;i++)
		{
			data=to_string(i);
			data="new_data"+data;
			config << " - path: " << data << ".tex" << endl;
 			config << "   content: [";
			for(unsigned int j(0); j < MAX_FILE;j++)
			{
				data=to_string(j);
				data="data"+data;
				for(unsigned int t(0); t < MAX_VAR;t++)
				{
					var=to_string(t);
					var=VAR+var;
					config <<  data << "_" << var << ",";
				}
				for(unsigned int t(0);t<MAX_EXPR-1;t++)
				{
					var=to_string(t);
					var=NEWVAR+var;
					config <<  var << "," << var+"_error,";
				}
			}
			var=to_string(MAX_EXPR-1);
			var=NEWVAR+var;
			config <<  var << "," << var+"_error" << "]" << endl;
			//var=VAR+var;
			//config <<  data << "_" << var << "]" << endl;

			config<<"   caption: This is a caption test for N@-O-Mi" << endl;
			config<<"   label: This is a label test for N@-O-Mi" << endl;
		}
		config.close();
	}	
	return 0;
}
