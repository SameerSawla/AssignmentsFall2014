#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include "player.h"
#include "scores.h"
#include "playergamedetails.h"

using namespace std;

//Returns true if input is a number, false if it is not
bool isANumber(std::string temp)
{	
	int tempNumber;
	std::istringstream iss( temp );
	iss >> tempNumber;
	return iss.eof();	
}

//Returns integer number literal-equivalent to string input
int returnANumber(std::string temp)
{
	int tempNumber;
	std::istringstream iss( temp );
	iss >> tempNumber;
	return tempNumber;
}

//Converts an integer number to string
std::string convertToString(int Number)
{
	if(Number==0)
	{
		return "-";
	}
	std::string Result;     // string which will contain the result

	std::ostringstream convert;  // stream used for the conversion

	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream

	return convert.str();
}

//Reading from the input file and populating in gameDetails vector
void readFromTheFile(std::string readMe,std::vector<PlayerGameDetails>& gameDetails)
{
	std::ifstream in_str(readMe.c_str());
	if(in_str==NULL)
	{
		std::cerr<<"\nERROR : Input file does not exist.\n";
		exit(1);
	}
	std::string temp = "";
	Player tempPlayer ;
	Scores tempScores ; 
	in_str>>temp;
	while(in_str)
	{	
		if(!isANumber(temp))
		{	
			if(!tempPlayer.isNull() && !tempScores.isNull())
			{
				PlayerGameDetails one;
				one.setPlayer(tempPlayer);
				one.setScores(tempScores);
				if(tempScores.getScoreVector().size()<12 || tempScores.getScoreVector().size()>20)
				{
					std::cerr<<"\nERROR : Wrong input, incorrect number of round scores for " <<tempPlayer.getFirstName()<<" "<<tempPlayer.getLastName()<<"\n";
					exit(1);
				}	
				gameDetails.push_back(one);
				tempScores.setNull();
			}
			tempPlayer.setFirstName(temp);
			in_str>>temp;
			tempPlayer.setLastName(temp);
			in_str>>temp;
			continue;
		}
		tempScores.push(returnANumber(temp));
		in_str>>temp;
	}

	if(tempScores.getScoreVector().size()<12 || tempScores.getScoreVector().size()>20)
		{
			std::cerr<<"\nERROR : Wrong input, incorrect number of round scores for " <<tempPlayer.getFirstName()<<" "<<tempPlayer.getLastName()<<"\n";
			exit(1);
		}

	if(!tempScores.isNull())
	{

			PlayerGameDetails one;
			one.setPlayer(tempPlayer);
			one.setScores(tempScores);
			gameDetails.push_back(one);
			tempScores.setNull();
		
	}

	

}

//Calculates the cumulative score of a Player's performance throughout the game
void calculateScore(PlayerGameDetails& one)
{
 int sum = 0;
 std::vector<int> temp2;	
 std::vector<int> temp = one.getScores().getScoreVector();
 for(unsigned int i=0,j=0;i<temp.size();i++)
 {
  if(temp[i]==10)
  {
  	if(i==0)
  	{
  		sum = sum + temp[i]+temp[i+1]+temp[i+2];
  		temp2.push_back(sum);
  		j++;
  	}
  	else
  	{
  		if(temp2.size()!=10) 
  		{
  		if(temp[i-1]!=0)
  		{
  				sum = sum + temp[i]+temp[i+1]+temp[i+2];
  			 	temp2.push_back(sum);	
  	
  		}
  		else
  		{ 		
  				sum = sum + temp[i-1]+temp[i] + temp[i+1] ; 
  				temp2.push_back(sum);
  		}
  		}
  	}
  }
  else
  {
  	if(temp2.size()!=10) 
  	{
  	if(temp[i]+temp[i+1]==10)
  	{	
  		sum = sum + temp[i]+temp[i+1]+temp[i+2];
  		temp2.push_back(sum);
  		i = i+1;
  	}
  	else
  	{
  		sum = sum + temp[i]+temp[i+1];
  		temp2.push_back(sum);
  		i=i+1;
  	}
    }
  }
 }
 //Setting calculated scores to cumulative scores
 one.setcumulativeScores(temp2);
}

//Sorting function to sort PlayerGameDetails objects based on cumulative scores.
bool Sort(const PlayerGameDetails& t1,const PlayerGameDetails& t2)
{	
	return t1.getCumulativeScores()[9]>t2.getCumulativeScores()[9];
}

//Alphabetical Sorting function to sort PlayerGameDetails objects.
bool SortAlphabetically(const PlayerGameDetails& t1,const PlayerGameDetails& t2)
{	
	if(t1.getPlayer().getLastName()==t2.getPlayer().getLastName())
	{
		return t1.getPlayer().getFirstName()<t2.getPlayer().getFirstName();
	}
	return t1.getPlayer().getLastName()<t2.getPlayer().getLastName();
}

//returns the maximum length of the names of the players.
int deduceMaxLength(std::vector<PlayerGameDetails> &gameDetails)
{
 int maxLength = 0;
 for(int i=0;i<gameDetails.size();i++)
 {
  if(gameDetails[i].getNameSize()>maxLength)
  {
  	maxLength = gameDetails[i].getNameSize();
  }
 }
 return maxLength;
}

//Writing the game score grid to the output file
void displayTheGrid(PlayerGameDetails &one,int maxSize,ofstream &out_str)
{
 std::string top_spaced;
 std::string top_line(maxSize + 66,'-');
 std::string intermediate_line(maxSize+2,' ');
 
 std::vector<int> splitScores = one.getScores().getScoreVector();
 std::vector<int> cumScores = one.getCumulativeScores();

 out_str<<top_line<<"\n";
 //Writing the Name and round scores to the output file
 out_str<<"| "<<std::setw(maxSize)<<std::left<<one.getPlayerName()<<" |";
 for(unsigned int i=0,j=0;i<10;i++,j++)
 {
 		if(splitScores[j]==10)
 		{
 			if(j==splitScores.size()-2)
 				{
 					out_str<<" "<<convertToString(splitScores[j])<<" "<<((splitScores[j+1]==10)?"X":""+splitScores[j+1])<<"   |";
 				}
 			else 
 				{
 					if(j==splitScores.size()-3 && i==9)
 					{	
 						std::string lastScore = convertToString(splitScores[j+2]);
 						if(splitScores[j+2]==10)
 						{
 							if(splitScores[j+1]==0)
 							{
 								lastScore = "/";
 							}
 							else
 							{
 								lastScore = "X";
 							}
 						}
 						else if(splitScores[j+2]==0)
 						{
 							lastScore = "-";
 						}
 						out_str<<" "<<((splitScores[j]==10)?"X":convertToString(splitScores[j]))<<" "<<((splitScores[j+1]==10)?"X":convertToString(splitScores[j+1]))<<" "<<lastScore<<" |";	
 						j++;
 					}
 					else
 					{
 						out_str<<"   X |";
 					}
 				}
 			
 		}
 		else
 		{
 			if(i!=9)
 			{
	 			if(splitScores[j]+splitScores[j+1]==10)
	 			{
	 				out_str<<" "<<convertToString(splitScores[j])<<" / |";
	 				j++;
	 			}
	 			else
	 			{
	 				out_str<<" "<<convertToString(splitScores[j])<<" "<<convertToString(splitScores[j+1])<<" |";
	 				j++;
	 			}
 			}
 			else
 			{
 				if(j==splitScores.size()-2)
 				{
 					out_str<<" "<<convertToString(splitScores[j])<<" "<<convertToString(splitScores[j+1])<<"   |";
 					j++;
 				}
 				else
 				{
 					out_str<<" "<<convertToString(splitScores[j])<<" "<<((splitScores[j]+splitScores[j+1]==10)?"/":convertToString(splitScores[j]))<<" "<<((splitScores[j+2]==10)?"X":convertToString(splitScores[j+2]))<<" |";	
 				}
 			}
 		}
  }	
 	
 out_str<<"\n";
 out_str<<"|"<<intermediate_line<<"|";
 top_spaced= "     |";
 //Writing the cumulative scores to the output file
 for(unsigned int i=0;i<10;i++)
 {
 	if(i!=9)
 	{
 		out_str<<" "<<std::setw(3)<<std::right<<cumScores[i]<<" |";
 	}
 	else
 	{
 		out_str<<" "<<std::setw(5)<<std::right<<cumScores[i]<<" |";
 	}
 }
 out_str<<"\n";
}
