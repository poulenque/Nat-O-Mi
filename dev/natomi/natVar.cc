#include "natVar.h"

//*************************
//Constructor && Destructor
//*************************
NatVariable::NatVariable(){}
NatVariable::NatVariable(const std::string& d, const std::string& v,const Unit& u, const std::string& e,size_t i,const double va):
data(d),var(v),unit(u),error(e),index(i),value(va){}
NatVariable::NatVariable(NatVariable& nat):
data(nat.data),var(nat.var),unit(nat.unit),error(nat.error),index(nat.index),value(nat.value){}
NatVariable::~NatVariable(){}

//***********************
//Cout operator << NatVar
//***********************
std::ostream& operator<<( std::ostream& out, const NatVariable& natvar)
{
	out << natvar.var << "[" << natvar.unit << "]" << "[" << natvar.error << "]";
	return out;
}
