#Natplot.py is the natomi interface for gnuplot
import natparser
from natparser import inputfile

def natomi_plot(gnpvar):

	with open(inputfile+".gnuplot",'w') as output:
		output.write("%This file is generated with N@-O-Mi-3.0\n")#Beurk?
		output.write("set terminal context standalone\n")
		output.write("set output '"+inputfile+".tex'\n")
		output.write("set title '"+gnpvar+"'\n")
		output.write("set autoscale\n")
		output.write("set xtics auto\n")
		output.write("set xlabel '"+gnpvar+"'\n")
		output.write("set ylabel '"+gnpvar+"'\n")
		output.write("set grid\n")

		output.write(gnpvar+"="+natparser.natfind_in_line(gnpvar,0)+"\n")

	output.closed
