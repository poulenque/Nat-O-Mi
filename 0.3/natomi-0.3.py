#!/usr/bin/env python

#Import Basic lib


#Modules from N@-O-Mi
import natparser
import natcore
import nattable
#---------------------
#Na-O-Mi Main
#---------------------


# define the list of lines to write at the end
write_list = [line.strip() for line in open(natparser.inputfile,'r') if line.strip()]

write_list = natparser.natomi_tab_to_space(write_list)
write_list = natparser.natomi_spaces_to_space(write_list)

#Compute columns with natomi_core
if natparser.args.formula:
	formula = natparser.args.formula[0]
	#Set the formula and the column
	write_list = natcore.natomi_core(write_list,formula)

	#new features with natomi_extra
if natparser.args.columnm:
	for column in natparser.args.columnm:
		write_list.append("#%The mean value of "+column
		+" is: "+str(natomi_mean(write_list,column)))

if natparser.args.columnd:
	for column in natparser.args.columnd:
		write_list.append("#%The deviation value of "+column
		+" is: "+str(natomi_deviation(write_list,column)))

#Finally we write the write_liste into the file
with open(natparser.outputfile,'w') as output:
	for line in write_list:
		output.write("%s\n" % ''.join(line))
output.closed

#The End
