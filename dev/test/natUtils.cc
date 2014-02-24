#include "natUtils.h"

ostream & operator<<(ostream& out,vector<string> v){
	for (const auto& t : v)
		out<<t<<" ";
	return out;
}

string DoubleToStr(double const x) {
	std::ostringstream oss;
	oss << x;
	return oss.str();
}

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

void skipBlanks(const string& str, size_t& pointer)
{
	for(;pointer < str.size();pointer++)
	{
		//Next line if comments, tabs or whitespace found
    	if(str[pointer]==COMMENT_SYMBOL)
		{	
			while(!(str[pointer] =='\n' || str[pointer] =='\r')) pointer++;
		}
		else if(!(str[pointer]==' ' || str[pointer]=='\t' || str[pointer] =='\n' || str[pointer] =='\r'))break;
	}
}
