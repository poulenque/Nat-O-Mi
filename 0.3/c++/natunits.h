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
	bool error	;
	int meter	;
	int g 		;
	int second 	;
	int Ampere 	;
	int Kelvin 	;
	int mol 	;
	int candela	;
	int special	;
public:
	Unit(int i=1, int j=1,double f=1);
	Unit(string name);
	string getname();
	friend Unit operator+ (Unit const & a ,Unit const & b);
	friend Unit operator- (Unit const & a ,Unit const & b);
	friend Unit operator* (Unit const & a ,Unit const & b);
	friend Unit operator/ (Unit const & a ,Unit const & b);
	friend bool operator==(Unit const & a ,Unit const & b);
	friend Unit operator* (Unit const & a ,double const & factor_double);
	friend Unit operator* (double const & factor_double, Unit const & a);
}Unit;

typedef struct NatDouble{
	Unit unit;
	double value;
}NatDouble;


void natUnitInit();

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