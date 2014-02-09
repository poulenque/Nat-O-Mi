#include "natData.h"

//*************************
//Constructor && Destructor
//*************************
Data::Data():pointer(0){}
Data::Data(const string& p):path(p),pointer(0){}

Data::~Data()
{
	//delete[] buffer; TODO every constructor and destructor
}

//*********************
//Data update vars Func
//*********************
bool Data::updateVars()
{
	string tmp;
	skipBlanks(buffer, pointer);

	if(buffer.size()==pointer)//TODO better to check EOF???
		return false;

	size_t i(0);
	//While we are still parsing the double
	while(strchr("\n\r", buffer[pointer])==NULL)//TODO think about that crap XD
	{
		while(strchr(" \t\n\r", buffer[pointer])==NULL)//TODO what if there is \n ERROR
		{
			tmp.push_back(buffer[pointer]);
			pointer++;
		}
		this->vars[i]->value = StrToDouble(tmp);
		tmp.clear();
		i++;

		//Then we go to the next var
		while(strchr(" \t", buffer[pointer])!=NULL && buffer.size()!=pointer)//TODO
			pointer++;
	}
	return true;
}
