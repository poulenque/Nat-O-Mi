#include "natunits.h"
#include <algorithm>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include <vector>

using namespace std;

static vector<int> const prime={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};

Unit const unit_error	= Unit(0,0,0);
Unit const unit_error_factor= Unit(0,0,1);
Unit const unit_none 	= Unit(1,1);
Unit const unit_meter	= Unit(prime[0],1);
Unit const unit_g 		= Unit(prime[1],1);
Unit const unit_second 	= Unit(prime[2],1);
Unit const unit_Ampere 	= Unit(prime[3],1);
Unit const unit_Kelvin 	= Unit(prime[4],1);
Unit const unit_mol 	= Unit(prime[5],1);
Unit const unit_candela = Unit(prime[6],1);
Unit const unit_special = Unit{prime[7],1};

static vector<vector<string> >prefix;
static vector<double> prefix_value;

void natUnitInit(){
			prefix.push_back({"Y","yotta"});
			prefix_value.push_back(1e24);

			prefix.push_back({"Z","zetta"});
			prefix_value.push_back(1e21);

			prefix.push_back({"E","exa"});
			prefix_value.push_back(1e18);

			prefix.push_back({"P","peta"});
			prefix_value.push_back(1e15);

			prefix.push_back({"T","tera"});
			prefix_value.push_back(1e12);

			prefix.push_back({"G","giga"});
			prefix_value.push_back(1e9);

			prefix.push_back({"M","mega"});
			prefix_value.push_back(1e6);

			prefix.push_back({"ma","myria"});
			prefix_value.push_back(1e4);

			prefix.push_back({"k","kilo"});
			prefix_value.push_back(1e3);

			prefix.push_back({"h","hecto"});
			prefix_value.push_back(1e2);

			prefix.push_back({"da","deca"});
			prefix_value.push_back(1e1);

			//NOTHING FOR 1e0

			prefix.push_back({"d","deci"});
			prefix_value.push_back(1e-1);

			prefix.push_back({"c","centi"});
			prefix_value.push_back(1e-2);

			prefix.push_back({"m","milli"});
			prefix_value.push_back(1e-3);

			prefix.push_back({"mo","myrio"});
			prefix_value.push_back(1e-4);

			prefix.push_back({"μ","micro"});
			prefix_value.push_back(1e-6);

			prefix.push_back({"n","nano"});
			prefix_value.push_back(1e-9);

			prefix.push_back({"p","pico"});
			prefix_value.push_back(1e-12);

			prefix.push_back({"f","femto"});
			prefix_value.push_back(1e-15);

			prefix.push_back({"a","atto"});
			prefix_value.push_back(1e-18);

			prefix.push_back({"z","zepto"});
			prefix_value.push_back(1e-21);

			prefix.push_back({"y","yocto"});
			prefix_value.push_back(1e-24);
}

Unit::Unit(int i, int j,double f):
p(i),
q(j),
factor(f),
error(false),
meter(0),
g(0),
second(0),
Ampere(0),
Kelvin(0),
mol(0),
candela(0),
special(0){
	natunitSimplify(*this);
}
Unit::Unit(string name):
p(),
q(),
factor(),
error(false),
meter(),
g(),
second(),
Ampere(),
Kelvin(),
mol(),
candela(),
special(){
	*this = str2unit(name);
}

ostream& operator<<(ostream& out, Unit & unit){
	out<<unit2str(unit);
	return out;
}


Unit operator+(Unit const & a,Unit const & b){
	if (a.p!=b.p)return unit_error;
	if (a.q!=b.q)return unit_error;
	if (a.factor!=b.factor) return unit_error_factor;
	//should be simplified already
	return a;
}

Unit operator-(Unit const & a,Unit const & b){
	return a+b;
}

Unit operator*(Unit const & a,Unit const & b){
	Unit ret(a);
	ret.p*=b.p;
	ret.q*=b.q;
	ret.factor*=b.factor;
	natunitSimplify(ret);
	ret.meter 	+=	b.meter;
	ret.g 		+=		b.g;
	ret.second 	+=	b.second;
	ret.Ampere 	+=	b.Ampere;
	ret.Kelvin 	+=	b.Kelvin;
	ret.mol 	+=		b.mol;
	ret.candela +=	b.candela;
	ret.special +=	b.special;
	return ret;
}

Unit operator/(Unit const & a,Unit const & b){
	Unit ret(a);
	ret.p*=b.q;
	ret.q*=b.p;
	ret.factor/=b.factor;
	natunitSimplify(ret);
	ret.meter 	-=	b.meter;
	ret.g 		-=	b.g;
	ret.second 	-=	b.second;
	ret.Ampere 	-=	b.Ampere;
	ret.Kelvin 	-=	b.Kelvin;
	ret.mol 	-=	b.mol;
	ret.candela -=	b.candela;
	ret.special -=	b.special;
	return ret;
}

bool operator==(Unit const & a,Unit const &b){
	if(a.p==b.p && a.q==b.q && a.factor==b.factor)return true;
	return false;
}

Unit operator*(Unit const & a,double const & factor_double){
	Unit ret(a);
	//this operation wont change the unit part,
	//so we don't need to simplify
	ret.factor*=factor_double;
	//natunitSimplify(ret);
	return ret;
}

Unit operator*(double const & factor_double, Unit const & a){
	return a*factor_double;
}

Unit str2unit_simple_suffixe(string name);

//name is modified, prefix is removed if understood
Unit str2unit_simple_prefix(string & name){

	//if cant read => might have a prefix
	if(str2unit_simple_suffixe(name)==unit_error){

		string name_lower=name;
		boost::algorithm::to_lower(name_lower);

		for(size_t i=0;i<prefix.size();i++){
			//short version -> 'm' and 'M' are different
			if(     name.substr(0,prefix[i][0].size())==prefix[i][0]){
				name = name.substr(1,prefix[i][0].size());
				return unit_none*prefix_value[i];
			}
			//long version -> "milli" and "Milli" are the same
			if(name_lower.substr(0,prefix[i][1].size())==prefix[i][1]){
				name = name.substr(prefix[i][1].size(),prefix[i][1].size());
				return unit_none*prefix_value[i];
			}
		}
	}
	return unit_none;
}

Unit str2unit_simple_suffixe(string name){
	string name_lower=name;
	boost::algorithm::to_lower(name_lower);
	//==========
	for(auto & str : {"","none"}){
		if(str==name_lower)
			return unit_none;
	}
	//===========
	for(auto & str : {"m","meter","meters"}){
		if(str==name_lower)
			return unit_meter;
	}
	//===========
	for(auto & str : {"g","grammes","gramme","gram"}){
		if(str==name_lower)
			return unit_g;
	}
	//===========
	for(auto & str : {"s","second","seconds"}){
		if(str==name_lower)
			return unit_second;
	}
	//===========
	for(auto & str : {"a","amp","amps","ampere","amperes"}){
		if(str==name_lower)
			return unit_Ampere;
	}
	//===========
	for(auto & str : {"k","kelvin","kelvins"}){
		if(str==name_lower)
			return unit_Kelvin;
	}
	//===========
	for(auto & str : {"mol","mols","mole","moles"}){
		if(str==name_lower)
			return unit_mol;
	}
	//===========
	for(auto & str : {"cd","candela","candelas"}){
		if(str==name_lower)
			return unit_candela;
	}
	//===========
	for(auto & str : {"x"}){
		if(str==name_lower)
			return unit_special;
	}
	return unit_error;

}

Unit str2unit_simple(string name){

	//prefix : name will be modified, 
	Unit factor = str2unit_simple_prefix(name);

	return factor*str2unit_simple_suffixe(name);
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
	//NEED A PARSER
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





