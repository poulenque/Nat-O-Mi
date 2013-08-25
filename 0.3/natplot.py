#Natplot.py is the natomi interface for gnuplot
import natparser
from natparser import inputfile

def natomi_plot(gnpargvar):

#	try:
#   		with open(inputfile+'.gnuplot'):
#			print("GnuPlot file already exists")
#			pass
#	except IOError:
		with open(inputfile+".gnuplot",'w') as output:
			output.write("%This file is generated with N@-O-Mi-3.0\n")#Beurk?
			output.write("set terminal context standalone\n")
			output.write("set output '"+(' '.join(gnpargvar)).replace(' ', '')+".tex'\n")
			output.write("set title '"+(' '.join(gnpargvar)).replace(' ', '')+"'\n")
			output.write("set autoscale\n")
			output.write("set grid\n")
			output.write("set xtics auto\n")
			output.write("set xlabel '"+gnpargvar[0]+"'\n")
			output.write("set ylabel '"+gnpargvar[1]+"'\n")
			output.write("set ytics auto\n")
			if len(gnpargvar)==3:
				output.write("set zlabel '"+gnpargvar[2]+"'\n")
				output.write("set ztics auto\n")


			for var in gnpargvar:
				output.write(var+"="+str(natparser.natfind_in_line(var,0))+"\n")

		output.closed
