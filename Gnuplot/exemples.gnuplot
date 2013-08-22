#Exemple de différent script gnuplot utile pour les tps
#plus d'infos sur: http://gnuplot.sourceforge.net/demo/

#Utilisation de ce script avec exemples.dat
#installer gnuplot et conText

#Pour compiler:
#gnuplot exemples.gnuplot
#context exple.tex

#Precise le type de sorti et le nom de sorti
set terminal context standalone
set output 'exple.tex' # fichier a compiler avec context

#POur appliquer du latex: '$ code latex $'

#Titre
set title 'Exemple de gnuplot, avec $\LaTeX$'

# scale axes automatically
set autoscale

#Configuration des axes
set xtics auto
set ytics auto

#set xrange [a:b] # [*:*] => autoscale
#set yrange [a:b]

set xlabel 'Angle $[^\circ]$'
set ylabel '$F_{portance}\ [mN] $'

#Precise la localisation des légendes,le titre,etc...
set key center top title " "

#Mettre une grille
set grid

#plot la courbe selon les data du fichier exemples
#using column X: columnY with lines,points, linepoints,etc....
plot 'exemple.dat' using 1:2 notitle with lines

#plot avec des errors il faut rajouter une colonne
#l'erreur est de 10% sur les mesures
plot 'exemple.dat' using 1:2:($2*0.1) notitle with yerrorbars 

#on peut plotter les deux sur la meme figure
# ', \' => saut de ligne
plot 'exemple.dat' using 1:2:($2*0.1) notitle with errorbars, \
     'exemple.dat' using 1:2 notitle with lines

#Multi axes:

#set x2label ''
set y2label '$F_{trainee}\ [mN] $'
#set x2range [a:b]
set y2range [*:*]
#set x2tics auto
set y2tics auto
#set xtics nomirror
set ytics nomirror # retire les tics de y1 sur l'axe y2

unset grid # on retire la grid c'est plus joli

#Plot avec le deuxieme axe d'ordonne
plot 'exemple.dat' using 1:2 title '$F_{portance}$' with lines axes x1y1, \
     'exemple.dat' using 1:3 title '$F_{trainee}$' with lines axes x1y2

#Création d'un champ vectoriel

#definitions d'une fonction qu'on va utiliser pour le fun
# ** est la puissance
d(x)=x**2

#création dun sample isometrique ???? XD
set isosample 31,31

#On retire les paramètre précédent qu'on veut plus
unset y2label
unset y2tics

#Plot du champ vectoriel seulement via un fichier !
plot 'exemple.dat' using 1:2:(d($1)):(d($1)) with vector notitle
