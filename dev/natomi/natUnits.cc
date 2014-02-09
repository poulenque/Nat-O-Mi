#include "natUnits.h"

Unit unit_error		;
Unit unit_none 		;
Unit unit_meter		;
Unit unit_g 		;
Unit unit_second 	;
Unit unit_Ampere 	;
Unit unit_Kelvin 	;
Unit unit_mol 		;
Unit unit_candela 	;
Unit unit_special 	;

static vector<vector<string> >prefix;
static vector<double> prefix_value;

void natUnitInit(){

			unit_error		= Unit("error");
			unit_none 		= Unit("none");
			unit_meter		= Unit("meter");
			unit_g 			= Unit("gram");
			unit_second 	= Unit("second");
			unit_Ampere 	= Unit("ampere");
			unit_Kelvin 	= Unit("Kelvin");
			unit_mol 		= Unit("mol");
			unit_candela 	= Unit("candela");
			unit_special 	= Unit("special");//Material etc...

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

Unit::Unit():
factor(1),
error(0),
meter(0),
g(0),
second(0),
Ampere(0),
Kelvin(0),
mol(0),
candela(0),
special(0)
{}


Unit::Unit(string name):
factor(),
error(),
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

ostream& operator<<(ostream& out, const Unit& unit){
	out<<unit2str(unit);
	return out;
}


Unit operator+(Unit const & a,Unit const & b){
	if(a.error || b.error) return unit_error;
	if(a==b)return a;
	return unit_error;
}

Unit operator-(Unit const & a,Unit const & b){
	return a+b;
}

Unit operator*(Unit const & a,Unit const & b){
	Unit ret(a);
	ret.factor*=b.factor;
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
	ret.factor/=b.factor;
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
	if(	a.meter		!= b.meter ||
		a.g			!= b.g ||
		a.second	!= b.second ||
		a.Ampere	!= b.Ampere ||
		a.Kelvin	!= b.Kelvin ||
		a.mol		!= b.mol ||
		a.candela	!= b.candela ||
		a.special	!= b.special)
		return false;
	
	double d=a.factor/b.factor;
	if (d>1.0001 || d<0.9999)
		return false;
	return true;
}

bool operator!=(Unit const & a,Unit const &b){
	return !(a==b);
}

Unit operator*(Unit const & a,double const & factor_double){
	Unit ret(a);
	ret.factor*=factor_double;
	return ret;
}

Unit operator*(double const & factor_double, Unit const & a){
	return a*factor_double;
}

Unit str2unit_simple_suffixe(const string & name);

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

Unit str2unit_simple_suffixe(const string & name){
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
	Unit ret=str2unit_simple_suffixe(name);
	if(ret!=unit_error){
		return ret;
	}
	//prefix : name will be modified
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
	if(name=="none"){
		ret.factor=1;
		ret.error=0;
		ret.meter=0;
		ret.g=0;
		ret.second=0;
		ret.Ampere=0;
		ret.Kelvin=0;
		ret.mol=0;
		ret.candela=0;
		ret.special=0;
	}else if(name=="error"){
		ret.factor=0;
		ret.error=1;
		ret.meter=0;
		ret.g=0;
		ret.second=0;
		ret.Ampere=0;
		ret.Kelvin=0;
		ret.mol=0;
		ret.candela=0;
		ret.special=0;
	}else if(name=="error_factor"){
		ret.factor=1;
		ret.error=1;
		ret.meter=0;
		ret.g=0;
		ret.second=0;
		ret.Ampere=0;
		ret.Kelvin=0;
		ret.mol=0;
		ret.candela=0;
		ret.special=0;
	}
	//=======
	//TODO
	//NEED A PARSER
	//=======
	return ret;
}

string unit2str(Unit unit){

	if(unit.error)
		return "UNIT_ERROR";

	string s;

	s+=DoubleToStr(unit.factor);

	if(unit.meter)
		s+="meter^{"+DoubleToStr(unit.meter)+"}";
	if(unit.g)
		s+="gram^{"+DoubleToStr(unit.meter)+"}";
	if(unit.second)
		s+="second^{"+DoubleToStr(unit.meter)+"}";
	if(unit.Ampere)
		s+="Ampere^{"+DoubleToStr(unit.meter)+"}";
	if(unit.Kelvin)
		s+="Kelvin^{"+DoubleToStr(unit.meter)+"}";
	if(unit.mol)
		s+="mol^{"+DoubleToStr(unit.meter)+"}";
	if(unit.candela)
		s+="candela^{"+DoubleToStr(unit.meter)+"}";
	if(unit.special)
		s+="special^{"+DoubleToStr(unit.meter)+"}";

	return s;
}


