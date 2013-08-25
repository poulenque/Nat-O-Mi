#ifndef NATUNITS_H
#define NATUNITS_H

#include <map>
#include <string>

using namespace std;

typedef struct Unit{
	int p;
	int q;
	double factor;
	Unit();
	Unit(int i, int j);
	Unit(string name);
	string getname();
}Unit;

Unit str2unit(string name);
string unit2str(Unit name);

ostream& operator<<(ostream& out, Unit & unit);

//on veut :
//
//creer des unites a partir de leur noms
//calculer des unites
//convertir les unites
//prendre en compte le facteur
//obtenir le nom
//



#endif