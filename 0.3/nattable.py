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