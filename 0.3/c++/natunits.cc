#include "natunits.h"
#include <algorithm>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include <muParser.h>
using namespace mu;

Unit::Unit(int i, int j=1){
	p=i;
	q=j;
}
Unit::Unit(){
	p=1;
	q=1;	
}
Unit::Unit(string name){
	*this = str2unit(name);
}

const Unit unit_error	= {0,0};
const Unit unit_none 	= {1,1};
const Unit unit_meter	= {2,1};
const Unit unit_Kg 		= {3,1};
const Unit unit_second 	= {5,1};
const Unit unit_Ampere 	= {7,1};
const Unit unit_Kelvin 	= {11,1};
const Unit unit_mol 	= {13,1};
const Unit unit_candela = {17,1};

using namespace std;

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

Unit str2unit(string name){
	//TODO
}

string unit2str(Unit unit){
	//TODO
	string s="TODO";
	return s;
}


ostream& operator<<(ostream& out, Unit & unit){
	out<<unit2str(unit)<<endl;
	return out;
}


Unit operator+(const Unit a,const Unit b){
	if (a.p!=b.p)return unit_error;
	if (a.q!=b.q)return unit_error;
	return a;
}

Unit operator-(const Unit a,const Unit b){
	return a+b;
}

Unit operator*(const Unit a,const Unit b){
	Unit ret(a);
	ret.p*=b.p;
	ret.q*=b.q;
	return ret;
}

Unit operator/(const Unit a,const Unit b){
	Unit ret(a);
	ret.p*=b.q;
	ret.q*=b.p;
	return ret;
}




