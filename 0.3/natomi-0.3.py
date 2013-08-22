#!/usr/bin/env python

#Import Basic lib
from math import * # import all math functions
import re

#Modules from N@-O-Mi
import natparser
import natcore
import nattable
#-----------------------------------------------------------------------
#Na-O-Mi Main
#-----------------------------------------------------------------------

#NEED TO SPECIFY A LIST OF INPUT FILES
for inputfile in args.inputfiles:

	# define the list of lines to write at the end
	write_list = [line.strip() for line in open(inputfile,'r') if line.strip()]

	#Compute columns with natomi_core
	if args.formula:
		formula = args.formula[0]
		#Set the formula and the column
		write_list = natomi_core(write_list,formula)

	#new features with natomi_extra
	if args.columnm:
		for column in args.columnm:
			write_list.append("#%The mean value of "+column
			+" is: "+str(natomi_mean(write_list,column)))

	if args.columnd:
		for column in args.columnd:
			write_list.append("#%The deviation value of "+column
			+" is: "+str(natomi_deviation(write_list,column)))

#Finally we write the write_liste into the file
	with open(outputfile,'w') as output:
		for line in write_list:
			output.write("%s\n" % ''.join(line))
	output.closed

#The End
