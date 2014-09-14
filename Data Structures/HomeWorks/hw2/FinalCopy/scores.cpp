#include <string>
#include <iostream>
#include "scores.h"

//Displaying the scores
void Scores::display()
{	
	std::cout<<"\n";
	for(unsigned int i=0;i<scoreSheet.size();i++)
	{
		std::cout<<scoreSheet[i]<<" ";
	}
	std::cout<<"\n";
}