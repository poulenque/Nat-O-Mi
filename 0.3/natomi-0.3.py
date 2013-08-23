#!/usr/bin/env python

#Import Basic lib


#Modules from N@-O-Mi
import natparser
import natcore
import nattable
import natplot
from natparser import _list
#---------------------
#Na-O-Mi Main
#---------------------


# define the list of lines to write at the end


#Compute columns with natomi_core
if natparser.args.formula:
	formula = natparser.args.formula[0]
	#Set the formula and the column
	_list = natcore.natomi_core(_list,formula)

	#new features with natomi_extra
if natparser.args.columnm:
	for column in natparser.args.columnm:
		_list.append("#%The mean value of "+column
		+" is: "+str(natomi_mean(_list,column)))

if natparser.args.columnd:
	for column in natparser.args.columnd:
		_list.append("#%The deviation value of "+column
		+" is: "+str(natomi_deviation(_list,column)))


if natparser.args.gnpvar:	
	natplot.natomi_plot(natparser.args.gnpvar)


#Finally we write the _list into the file
with open(natparser.outputfile,'w') as output:
	for line in _list:
		output.write("%s\n" % ''.join(line))
output.closed

#The End
