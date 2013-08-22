import sys
import argparse
import re

#Parse options
args = sys.argv

#Na-O-Mi 2.0 args
parser = argparse.ArgumentParser(conflict_handler='resolve')
parser.add_argument('-v','--version', action='version', version='N@-O-Mi 2.0')
parser.add_argument('-i', dest='inputfiles',type=str,
	help='Specify the input files',action='store',required = True)
parser.add_argument('-o', dest='outpufiles',type=str,
	help='Specify the output files',action='store',required = True)
parser.add_argument('-f', dest='formula',nargs=1,type=str,
	help='Specify the formula to apply',action='store')
parser.add_argument('-m',dest='columnm',nargs='+',type=str,metavar='COLUMN',
	help='Ask for the mean value of the specified column')
parser.add_argument('-d',dest='columnd',nargs='+',type=str,metavar='COLUMN',
	help='Ask for deviation value of the specified column')

#Na-O-Mi 3.0 args
#parser.add_argument('-t', dest='table',nargs=2,type=str,
#	help='Create a table with caption and label',action='store',metavar=('CAPTION', 'LABEL'))


#USEFUL VARIABLES
args = parser.parse_args()
inputfile = args.inputfiles
outputfile = args.outpufiles



#USEFUL FUNCTIONS

#Na-O-Mi first line parser
def natomi_line_parse(lines):
	return re.sub('\(.*?\)','',lines[0]).split(' ')

#Na-O-Mi is line commented
def natomi_is_commented(line):
	return '#' in line

#Na-O-Mi is line hardcommented
def natomi_is_hardcomt(line):
	return '%' in line

#Na-O-Mi extra info writer
def natomi_append_extra(outputfile,info):
	with open(outputfile,'a') as output:
		output.write("#"+info+"\n")
	output.closed

#Na-O-Mi Replace all tabs by spaces
def natomi_tab_to_space(rowlist):
	return [row.replace('\t', ' ') for row in rowlist]

#Na-O-Mi Replace consecutive spaces to single space
def natomi_spaces_to_space(rowlist):
	return [' '.join(row.split()) for row in rowlist]
