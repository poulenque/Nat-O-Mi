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


#Na-O-Mi extra info writer
def natomi_append_extra(outputfile,info):
	with open(outputfile,'a') as output:
		output.write("#"+info+"\n")
	output.closed
