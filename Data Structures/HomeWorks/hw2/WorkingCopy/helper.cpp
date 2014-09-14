#include<string>
#include<sstream>

bool isANumber(std::string temp)
{	
	int tempNumber;
	std::istringstream iss( temp );
	iss >> tempNumber;
	return iss.eof();	
}