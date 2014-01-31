#include "natVar.h"


NatVariable::NatVariable(){}
NatVariable::NatVariable(const std::string& d, const std::string& v, const Unit& u, const std::string& e):
data(d),var(v),unit(u),error(e){}

//***********************
//Cout operator << NatVar
//***********************
std::ostream& operator<<( std::ostream& out, const NatVariable& natvar)
{
	out << "In: " << natvar.data << " " << natvar.var << "[" << natvar.unit << "]" << "[" << natvar.error << "]";
	return out;
}
