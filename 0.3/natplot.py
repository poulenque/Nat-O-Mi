#Natplot.py is the natomi interface for gnuplot

def natomi_table(gnuplotfile):
	with open(gnuplotfile+".gnuplot",'w',encoding='utf-8') as output:
		output.write("%This file is generated with N@-O-Mi-3.0\n")#Beurk?
	output.closed
	with open(gnuplotfile+".gnuplot",'a',encoding='utf-8') as output:
		output.write("set terminal context standalone\n")
		output.write("set output '"+gnuplotfile"+.tex'\n")
		output.write("set title '"+title+"'\n")
		output.write("set autoscale\n")
		output.write("set xtics auto\n")
		output.write("   columns={"+re.sub(' ',',',write_list[0])+"},\n")
		#Writing of the columns specification
		for name in write_list[0].split(' '):
			output.write("   columns/"+name+"/.style={column type=|c|,column name=$"+name+"$},\n")


		output.write("]{"+outputfile+"}\n")
		output.write(" \\caption{"+table_caption+"}\label{tab:"+table_label+"}\n")
		output.write("\\end{table}\n")
	output.closed
