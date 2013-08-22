#!/usr/bin/python-3.2.3

#Import
from math import * # import all math functions
import sys
import argparse
import re

#Name the useful constant

#Parse options
args = sys.argv

#Na-O-Mi 2.0 args
parser = argparse.ArgumentParser(conflict_handler='resolve')
parser.add_argument('-v','--version', action='version', version='N@-O-Mi 2.0')
parser.add_argument('-i', dest='inputfiles',nargs='+',type=str,
	help='Specify the input files',action='store',required = True)
parser.add_argument('-o', dest='outpufiles',nargs='+',type=str,
	help='Specify the output files',action='store',required = True)
parser.add_argument('-f', dest='formula',nargs=1,type=str,
	help='Specify the formula to apply',action='store')
parser.add_argument('-m',dest='columnm',nargs='+',type=str,metavar='COLUMN',
	help='Ask for the mean value of the specified column')
parser.add_argument('-d',dest='columnd',nargs='+',type=str,metavar='COLUMN',
	help='Ask for deviation value of the specified column')

#Na-O-Mi 3.0 args
parser.add_argument('-t', dest='table',nargs=2,type=str,
	help='Create a table with caption and label',action='store',metavar=('CAPTION', 'LABEL'))


args = parser.parse_args()

print(args.table[0]+" "+args.table[1])
table_caption=args.table[0]
table_label=args.table[1]

#####################################################################
#Na-O-Mi MAIN
#####################################################################


#Na-O-Mi first line parser
def natomi_line_parse(lines):
	return re.sub('\(.*?\)','',lines[0]).split(' ')

#Na-O-Mi is line commented
def natomi_is_commented(line):
	return '#' in line

#Na-O-Mi is line hardcommented
def natomi_is_hardcomt(line):
	return '%' in line

#Na-O-Mi core functions
def natomi_core(lines,formula):
	#Parse the input file
	column_names = natomi_line_parse(lines)
	#Write the first line of the file, since it isnot a comment
	write_list = []
	write_list.append(''.join(lines[0]))

	#Recopy and insert columns of the input to the outpufile
	for row in lines[1:]:
		splitrow = row.split(' ')
		newrow = []

		if natomi_is_commented(row): # ignore the comment lines
			if not natomi_is_hardcomt(row):
				write_list.append(' '.join(splitrow))
			continue

		for k in column_names:
		#Set the title variable, check if its float!
			try:
				exec(k+'='+'float(splitrow['+str(column_names.index(k))+'])')
			except ValueError:
				exec(k+'='+'splitrow['+str(column_names.index(k))+']')

		#Formula to compute the values
		exec(formula)
		#We clear the splitrow list and rebuilt it with the computed values

		for k in column_names:
			exec("newrow.append(str(" + k + "))")

		#Write finally into the outputfile
		write_list.append(' '.join(newrow))
	return write_list

#Na-O-Mi mean value computing
def natomi_mean(lines,column):
	#Define the mean float	
	nmean = 0
	n = 0 # the number of lines to divide for the mean value
	#----
	column_index = natomi_line_parse(lines).index(column)
	for line in lines[1:]:
		if not natomi_is_commented(line):
			try:
				n += 1
				nmean += float(line.split(' ')[column_index])
			except ValueError:
				print("The column "+column+" isn't filled with floats only!")
				sys.exit(1)
	return nmean/n

#Na-O-Mi deviation computing
def natomi_deviation(lines,column):
	mean = natomi_mean(lines,column)
	sqsigma = 0 # partial deviation
	n = 0 # the number of lines to divide for the deviation value
	#----
	column_index = natomi_line_parse(lines).index(column)
	for line in lines[1:]:
		if not natomi_is_commented(line):
			n += 1
			sqsigma += (float(line.split(' ')[column_index]) - mean)**2
	return (sqsigma/n)**(0.5)

#Na-O-Mi extra info writer
def natomi_append_extra(outputfile,info):
	with open(outputfile,'a') as output:
		output.write("#"+info+"\n")
	output.closed

#-----------------------------------------------------------------------
#Na-O-Mi core launch
#-----------------------------------------------------------------------

#NEED TO SPECIFY A LIST OF INPUT FILES
for inputfile in args.inputfiles:

	# define the list of lines to write at the end
	write_list = [line.strip() for line in open(inputfile,'r') if line.strip()]
	
	#if the -o option isnot given
	outputfile = inputfile
	#otherwise
	if args.outpufiles:
		outputfile = args.outpufiles[args.inputfiles.index(inputfile)]

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



#Natomi 3.0, Tex core table
	with open("table_"+outputfile+".tex",'w',encoding='utf-8') as output:
		output.write("%This file is generated with N@-O-Mi-3.0\n")#Beurk?
	output.closed
	with open("table_"+outputfile+".tex",'a',encoding='utf-8') as output:
		output.write("\\begin{table}\n")
		output.write(" \\centering\n")
		output.write(" \pgfplotstabletypeset[\n")
		output.write("   every head row/.style={before row=\hline,after row=\hline},\n")
		output.write("   every last row/.style={after row=\hline},\n")
		output.write("   columns={"+re.sub(' ',',',write_list[0])+"},\n")
		#Writing of the columns specification
		for name in write_list[0].split(' '):
			output.write("   columns/"+name+"/.style={column type=|c|,column name=$"+name+"$},\n")


		output.write("]{"+outputfile+"}\n")
		output.write(" \\caption{"+table_caption+"}\label{tab:"+table_label+"}\n")
		output.write("\\end{table}\n")
	output.closed

#The End
