#include "natUtils.h"

#include <sstream>

using namespace std;

ostream & operator<<(ostream& out,vector<string> v){
	for (const auto& t : v)
		out<<t<<" ";
	return out;
}

string double2str(double const x) {
	std::ostringstream oss;
	oss << x;
	return oss.str();
}

double str2double( const string s ) {
	std::istringstream i(s);
	double x;
	if (!(i >> x))
		std::cout<<"str2double failed\n";
		//TODO ERROR
//		return 0;
	return x;
} 

// Function string to double
double StrToDouble(std::string const& s)
{
	double value;
    try {
        value = boost::lexical_cast<double>(s);
    } catch (boost::bad_lexical_cast const& e){
		value = std::numeric_limits<double>::quiet_NaN();
    }
	return value;
}


//TODO move somewhere else with other stuff? template?? yes NATUTILS
//*******************************
//Function to find prefix of maps
//*******************************
/*MetaName::const_iterator findPrefix(const MetaName& map, const string& search_for) {
    MetaName::const_iterator i = map.lower_bound(search_for);
    if (i != map.end()) {
        const string& key = i->first;
        if (key.compare(0, search_for.size(), search_for) == 0) // Really a prefix?
            return i;
    }
    return map.end();
}*/
