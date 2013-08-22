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
				exec(k+'='+'splitrow['+str(column_names.index(k))+']')#TODO wtf???

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