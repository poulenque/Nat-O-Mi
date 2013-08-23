#Natomi 3.0, Tex core table

def natomi_table(outputfile):
	with open("table_"+outputfile+".tex",'w',encoding='utf-8') as output:
		output.write("%This file is generated with N@-O-Mi-3.0\n")#Beurk?
	output.closed
	with open("table_"+outputfile+".tex",'a',encoding='utf-8') as output:
		output.write("\\begin{tabular}{")

		#loop{{{
			##TODO
			output.write("|l")
		#}}}

		output.write("|}\n")


		output.write("\t\\hline\n")
		#TITLE
		output.write("\t")
		output.write( re.sub('\(.*?\)','' ,re.sub(' ',' & ',write_list[0]) ) )
		output.write("\n")


		#CONTENT=========================================
					#loop{{{
						##TODO
						output.write("\t\\hline\n")
						output.write("\t")
						#loop{{{
							#output.write( var)
							output.write( "& ")
						#}}}
						#output.write( var0 )
						output.write("\n")

					#}}}

		#END CONTENT======================================

		output.write("\t\\hline\n")
		output.write("\\end{tabular}\n")




		# output.write("\\begin{table}\n")
		# output.write("\t\\centering\n")
		# output.write("\t\pgfplotstabletypeset[\n")
		# output.write("\t\tevery head row/.style={before row=\hline,after row=\hline},\n")
		# output.write("\t\tevery last row/.style={after row=\hline},\n")
		# output.write("\t\tcolumns={"+re.sub(' ',',',write_list[0])+"},\n")
		# #Writing of the columns specification
		# for name in write_list[0].split(' '):
		# 	output.write("\t\tcolumns/"+name+"/.style={column type=|c|,column name=$"+name+"$},\n")

		# output.write("]{"+outputfile+"}\n")
		# output.write("\t\\caption{"+table_caption+"}\label{tab:"+table_label+"}\n")
		# output.write("\\end{table}\n")

	output.closed





