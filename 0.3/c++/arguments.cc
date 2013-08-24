#include "arguments.h"
#include <iostream>

static Args args;

Args get_args(){
	return args;
}

void process_args(int argc, char* argv[]){

	int temp=0;
	bool exitting=false;

	while(++temp!=argc){
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
			if(++temp!=argc)
				args.to_calculate_mean.push_back(argv[temp]);
		}else if(s=="-d"){
			if(++temp!=argc)
				args.to_calculate_deviation.push_back(argv[temp]);
		}else if(s=="-g"){
			if(++temp!=argc)
				args.to_calculate_gnuplot.push_back(argv[temp]);
		}else {
			cout<<"argument \""<<s<<"\""<< "doesn\'t mean anything."<<endl;
			exitting=true;
		}
	}
	
	if(args.input_file_path==""){
		cout<<"input file path missing, please use -i INPUTFILE "<<endl;
		exitting=true;
	}
	if(args.output_file_path==""){
		cout<<"output file path missing, please use -o OUTPUTFILE "<<endl;
		exitting=true;
	}
	if(exitting)exit(0);

}
