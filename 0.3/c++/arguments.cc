#include "arguments.h"
#include <iostream>
#include <string.h>

static Args args;

Args get_args(){
	return args;
}

void process_args(int argc, char* argv[]){

	int temp=0;
	bool exiting=false;
	char argumentator = '-';

	while(++temp<argc){
		string s = argv[temp];
		if(s=="-h"||s=="--help"){
			cout<<" 	usage: natomi-0.3.py [-h] [-v] -i INPUTFILES -o OUTPUFILES [-f FORMULA]"<<endl;
			cout<<"                      [-m COLUMN [COLUMN ...]] [-d COLUMN [COLUMN ...]]"<<endl;
			cout<<"                      [-g GNPVAR [GNPVAR ...]]"<<endl;
			cout<<endl;
			cout<<" optional arguments:"<<endl;
			cout<<"   -h, --help            show this help message and exit"<<endl;
			cout<<"   -v, --version         show program's version number and exit"<<endl;
			cout<<"   -i INPUTFILES         Specify the input files"<<endl;
			cout<<"   -o OUTPUFILES         Specify the output files"<<endl;
			cout<<"   -f FORMULA            Specify the formula to apply"<<endl;
			cout<<"   -m COLUMN [COLUMN ...]"<<endl;
			cout<<"                         Ask for the mean value of the specified column"<<endl;
			cout<<"   -d COLUMN [COLUMN ...]"<<endl;
			cout<<"                         Ask for deviation value of the specified column"<<endl;
			cout<<"   -g GNPVAR [GNPVAR ...], --gnuplot GNPVAR [GNPVAR ...]"<<endl;
			cout<<"                         Create gnuplot script file"<<endl;

		}
		else if(s=="-v"||s=="--version"){
			cout<<"Nat-O-Mi version : "<<Nat_O_Mi_VERSION__<<endl;
			exit(1);
		}else if(s=="-i"){
			if(++temp!=argc)
				args.input_file_path=argv[temp];
		}else if(s=="-o"){
			if(++temp!=argc)
				args.output_file_path=argv[temp];
		}else if(s=="-f"){
			if(++temp!=argc)
				args.formula = argv[temp];
		}else if(s=="-m"){
			while(++temp<argc && (char)argv[temp][0]!=argumentator){
				args.to_calculate_mean.push_back(argv[temp]);
			}
			if((char)argv[temp][0]==argumentator)temp--;
		}else if(s=="-d"){
			while(++temp<argc && (char)argv[temp][0]!=argumentator){
				args.to_calculate_deviation.push_back(argv[temp]);
			}
			if((char)argv[temp][0]==argumentator)temp--;
		}else if(s=="-g"){
			while(++temp<argc && (char)argv[temp][0]!=argumentator){
				args.to_calculate_gnuplot.push_back(argv[temp]);
			}
			if((char)argv[temp][0]==argumentator)temp--;
		}else {
			cout<<"argument \""<<s<<"\""<< " doesn\'t mean anything."<<endl;
			exiting=true;
		}
	}
	
	if(args.input_file_path==""){
		cout<<"input file path missing, please use -i INPUTFILE "<<endl;
		exiting=true;
	}
	if(args.output_file_path==""){
		cout<<"output file path missing, please use -o OUTPUTFILE "<<endl;
		exiting=true;
	}
	if(exiting)exit(0);

}
