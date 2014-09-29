#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include "helper.h"

using namespace std;


int main(int argc,char* argv[])
{	
	//Checking for proper number of arguments
	if(argc!=3)
	{
		std::cerr<<"Invalid number of arguments. \nRequired number of arguments : 2\n";
		return EXIT_FAILURE;
	}
	//Check for if the file exists or not 

	std::string inputFileName = argv[1];
	std::string outputFileName = argv[2];
	ofstream out_str;
	out_str.open(argv[2]);

	std::vector<PlayerGameDetails> gameDetails;

	//Reading from the input file
	readFromTheFile(inputFileName,gameDetails);

	//Deducing the maximum length of full name of the players
	int maxLength = deduceMaxLength(gameDetails);
	for(unsigned int i=0;i<gameDetails.size();i++)
	{
		calculateScore(gameDetails[i]);	
	}

	//Sorting alphabetially
	std::sort(gameDetails.begin(),gameDetails.end(),SortAlphabetically);

	//Displaying the score grid
	for(int i=0;i<gameDetails.size();i++)
	{
		displayTheGrid(gameDetails[i],maxLength,out_str);
	}

	std::string top_line(maxLength+66,'-');
	out_str<<top_line<<"\n\n";

	//Sorting based on highest cumulative scores
	std::sort(gameDetails.begin(),gameDetails.end(),Sort);

	//Displaying the final Scores
	for(unsigned int i=0;i<gameDetails.size();i++)
	{
		out_str<<std::setw(maxLength)<<std::left<<gameDetails[i].getPlayerName()<<"  "<<std::setw(3)<<std::right<<gameDetails[i].getCumulativeScores()[9]<<"\n";
	}

	return EXIT_SUCCESS;
}