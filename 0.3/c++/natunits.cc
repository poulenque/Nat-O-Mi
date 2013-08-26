#include "natunits.h"
#include <algorithm>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include <muParser.h>

using namespace mu;
using namespace std;


const Unit unit_error	= Unit(0,0);
const Unit unit_none 	= Unit(1,1);
const Unit unit_meter	= Unit(2,1);

const Unit unit_Kg 		= Unit(3,1,1000);
const Unit unit_g 		= Unit(3,1);

const Unit unit_second 	= Unit(5,1);
const Unit unit_Ampere 	= Unit(7,1);
const Unit unit_Kelvin 	= Unit(11,1);
const Unit unit_mol 	= Unit(13,1);
const Unit unit_candela = Unit(17,1);


Unit::Unit(int i, int j,double f){
	p=i;
	q=j;
	factor=f;
	natunitSimplify(*this);
}
Unit::Unit(string name){
	*this = str2unit(name);
}

ostream& operator<<(ostream& out, Unit & unit){
	out<<unit2str(unit);
	return out;
}


Unit operator+(const Unit a,const Unit b){
	if (a.p!=b.p)return unit_error;
	if (a.q!=b.q)return unit_error;
	//should be simplified already
	return a;
}

Unit operator-(const Unit a,const Unit b){
	return a+b;
}

Unit operator*(const Unit a,const Unit b){
	Unit ret(a);
	ret.p*=b.p;
	ret.q*=b.q;
	ret.factor*=b.factor;
	natunitSimplify(ret);
	return ret;
}

Unit operator/(const Unit a,const Unit b){
	Unit ret(a);
	ret.p*=b.q;
	ret.q*=b.p;
	ret.factor/=b.factor;
	natunitSimplify(ret);
	return ret;
}

Unit str2unit_simple(string name){
	boost::algorithm::to_lower(name);
	//==========
	for(auto & str : {"","none"}){
		if(str==name)
			return unit_none;
	}
	//===========
	for(auto & str : {"m","meter","meters"}){
		if(str==name)
			return unit_meter;
	}
	//===========
	for(auto & str : {"kg","kilogrammes","kilogramme","kilogram"}){
		if(str==name)
			return unit_Kg;
	}
	//===========
	for(auto & str : {"s","second","seconds"}){
		if(str==name)
			return unit_second;
	}
	//===========
	for(auto & str : {"a","amp","amps","ampere","amperes"}){
		if(str==name)
			return unit_Ampere;
	}
	//===========
	for(auto & str : {"k","kelvin","kelvines"}){
		if(str==name)
			return unit_Kelvin;
	}
	//===========
	for(auto & str : {"mol","mols","mole","moles"}){
		if(str==name)
			return unit_mol;
	}
	//===========
	for(auto & str : {"cd","candela","candelas"}){
		if(str==name)
			return unit_candela;
	}
	return unit_error;
}

//====================================
//====================================
//====================================
//====================================
//TODO
Unit str2unit(string name){
	Unit ret;
	//=======
	//TODO
	//=======
	natunitSimplify(ret);
	return ret;
}

string unit2str(Unit unit){
	//====
	//TODO
	//====
	string s="TODO (unit2str)";
	return s;
}

void natunitSimplify(Unit& unit){
	//====
	//TODO
	//====
}





