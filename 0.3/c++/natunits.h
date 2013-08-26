#ifndef NATUNITS_H
#define NATUNITS_H

#include <map>
#include <string>

using namespace std;

typedef struct Unit{
private:
	int p;
	int q;
	double factor;
public:
	Unit(int i=1, int j=1,double f=1);
	Unit(string name);
	string getname();
	friend Unit operator+(const Unit a,const Unit b);
	friend Unit operator-(const Unit a,const Unit b);
	friend Unit operator*(const Unit a,const Unit b);
	friend Unit operator/(const Unit a,const Unit b);
}Unit;

Unit str2unit(string name);
string unit2str(Unit name);

void natunitSimplify(Unit& unit);

ostream& operator<<(ostream& out, Unit & unit);

//on veut :
//
//convertir les unites
//prendre en compte le facteur
//



#endif