#ifndef natUnits_h
#define natUnits_h

#include "natUtils.h"

typedef struct Unit{
private:
	double factor;
	int error	;
	int meter	;
	int g 		;
	int second 	;
	int Ampere 	;
	int Kelvin 	;
	int mol 	;
	int candela	;
	int special	;
public:
	Unit();
	Unit(std::string name);
	~Unit(){};
	std::string getname();
	friend Unit operator+ (Unit const & a ,Unit const & b);
	friend Unit operator- (Unit const & a ,Unit const & b);
	friend Unit operator* (Unit const & a ,Unit const & b);
	friend Unit operator/ (Unit const & a ,Unit const & b);
	friend bool operator==(Unit const & a ,Unit const & b);
	friend Unit operator* (Unit const & a ,double const & factor_double);
	friend Unit operator* (double const & factor_double, Unit const & a);
	friend std::string unit2str(Unit name);
	friend Unit str2unit(std::string name);
}Unit;

typedef struct NatNumber{
	Unit unit;
	double value;
	std::string value_str;
}NatNumber;


void natUnitInit();

std::string unit2str(Unit name);
Unit str2unit(std::string name);

std::ostream& operator<<(std::ostream& out, const Unit& unit);

//on veut :
//
//convertir les unites
//prendre en compte le facteur
//



#endif
