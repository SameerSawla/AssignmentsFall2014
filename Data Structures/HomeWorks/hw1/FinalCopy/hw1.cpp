#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;

//Calculates the text to be pushed in each line of the formed user selected polygon
string mid_dataF(int count, int &pointerLocation,string userEnteredString)
{
 
 string result;
 for(unsigned int i=0;i<count;i++)
 {
 	result = result + userEnteredString[pointerLocation];
 	pointerLocation++;
 	pointerLocation = pointerLocation%(userEnteredString.size());
 }
 return result;
}

//Calculates the character text to be pushed in each line of the formed user selected polygon
char getCharMid_DataF(int &pointerLocation,string userEnteredString)
{
 char result = userEnteredString[pointerLocation];
 pointerLocation++;
 pointerLocation = pointerLocation%(userEnteredString.size());
 return result;
}

//Processes Right Triangle Polygon
string ProcessRightTriangle(int heightOfPolygon,string userEnteredString)
{
			int pointerLocation = 0;
			string resultString = "";
			string start_one = "*";
			string start_two = "**";
			string end(heightOfPolygon,'*');
			resultString = resultString + start_one + "\n";
			resultString = resultString + start_two + "\n";
			for(unsigned int i=0;i<heightOfPolygon-3;i++)
			{	
				
				resultString = resultString + "*";
				resultString = resultString + mid_dataF(i+1,pointerLocation,userEnteredString);
				resultString = resultString + "*\n";
			}
			resultString = resultString + end + "\n";	
			return resultString;
}

//Processes Square Polygon
string ProcessSquare(int heightOfPolygon,string userEnteredString)
{
			int pointerLocation = 0;
			string resultString = "";
			int midDataHeight = heightOfPolygon-2;
			string start_end(heightOfPolygon,'*');
			string mid_data(midDataHeight,' ');
			resultString = resultString + start_end + "\n";
			for(unsigned int i=0;i<heightOfPolygon-2;i++)
			{	
				
				resultString = resultString + "*";
				resultString = resultString + mid_dataF(midDataHeight,pointerLocation,userEnteredString);
				resultString = resultString + "*\n";		
				
			}
			resultString = resultString + start_end + "\n";
			return resultString;

}


//Processes Isosceles Triangle Polygon
string ProcessIsoscelesTriangle(int heightOfPolygon,string userEnteredString)
{
		int pointerLocation = 0;
		string resultString="";						
		for(unsigned int i=0;i<heightOfPolygon-1;i++)
			{	
				string spaced(heightOfPolygon-1-i,' ');
				resultString = resultString + spaced + "*";
				if(i!=0)	
				{
					resultString = resultString + mid_dataF(2*i-1,pointerLocation,userEnteredString);
					resultString = resultString + "*\n";
				}
				else
				{
					resultString = resultString + "\n";
				}
				
			}

		string endIt(2*heightOfPolygon-1,'*');
		resultString = resultString + endIt;
		return resultString;

}

//Processes Parallelogram Polygon
string ProcessParallelogram(int heightOfPolygon,string userEnteredString)
{
		int pointerLocation = 0;
		string startIt(2*heightOfPolygon-2,'*');
		string resultString="";						
		for(unsigned int i=0;i<heightOfPolygon-1;i++)
			{	
				string spaced(heightOfPolygon-1-i,' ');
				resultString = resultString + spaced + "*";
				if(i!=0)	
				{
					resultString = resultString + mid_dataF(2*heightOfPolygon-3,pointerLocation,userEnteredString);
					resultString = resultString + "*\n";
				}
				else
				{
					resultString = resultString + startIt+ "\n";
				}
				
			}

		string endIt(2*heightOfPolygon-1,'*');
		resultString = resultString + endIt;
		return resultString;

}


//Processes House Polygon
string ProcessHouse(int heightOfPolygon,string userEnteredString)
{
		int pointerLocation = 0;
 		int finalHeight = 0;
		string startIt(2*heightOfPolygon-3,'*');
		string resultString="";						
		for(unsigned int i=0;i<heightOfPolygon-1;i++)
			{	
				string spaced(heightOfPolygon-1-i,' ');
				resultString = resultString + spaced + "*";
				if(i!=0)	
				{	
					resultString = resultString + mid_dataF(2*heightOfPolygon-3,pointerLocation,userEnteredString) + mid_dataF(2*i-1,pointerLocation,userEnteredString);
					resultString = resultString + "*\n";
				}
				else
				{
					resultString = resultString + startIt+ "\n";
				}
				
				if(i==(heightOfPolygon-2))
				{
					finalHeight = 2*heightOfPolygon-1 + 2*i;
				}
			}

		string endIt(finalHeight+1,'*');
		resultString = resultString + endIt + "\n";
		for(int i=0;i<heightOfPolygon;i++)
		{
		string spacedTwo(1,' ');
		if(i==heightOfPolygon-1)
		{
			resultString = resultString + spacedTwo;
			string starred(finalHeight-1,'*');
			resultString = resultString + starred + "\n";
			continue;
		}
		
		resultString = resultString + spacedTwo + "*";
		resultString = resultString + mid_dataF(finalHeight-3,pointerLocation,userEnteredString) + "*\n";

		}

		for(int i=0;i<=heightOfPolygon/2;i++)
		{
			int pathLength = (finalHeight+1)/3;
			string pathSpace1(pathLength+i,' ');
			string pathSpace2(pathLength,' ');
			resultString = resultString + pathSpace1+"*"+mid_dataF(pathLength,pointerLocation,userEnteredString)+"*\n";
		}

		return resultString;

}

//Processes Trapezium Polygon
string ProcessTrapezium(int heightOfPolygon,string userEnteredString)
{
 		int pointerLocation = 0;
 		int finalHeight = 0;
		string startIt(2*heightOfPolygon-3,'*');
		string resultString="";						
		for(unsigned int i=0;i<heightOfPolygon-1;i++)
			{	
				string spaced(heightOfPolygon-1-i,' ');
				resultString = resultString + spaced + "*";
				if(i!=0)	
				{
					resultString = resultString + mid_dataF(2*heightOfPolygon-3,pointerLocation,userEnteredString);
					resultString = resultString + mid_dataF(2*i-1,pointerLocation,userEnteredString);
					resultString = resultString + "*\n";
				}
				else
				{
					resultString = resultString + startIt+ "\n";
				}
				
				if(i==(heightOfPolygon-2))
				{
					finalHeight = 2*heightOfPolygon-1 + 2*i;
				}
			}

		string endIt(finalHeight+1,'*');
		resultString = resultString + endIt;
		return resultString;
}


//Processes X-Shape Polygon
string ProcessXShape(int heightOfPolygon,string userEnteredString)
{
 	int x = heightOfPolygon;
 	string resultString = "";
	char chars[x];
    int pointerLocation = 0;  
    for (int i = 0; i < x; i++) {
        chars[i] = '*';
        chars[x - 1 - i] = '*';
        for (int j = 0; j < x; j++) {
            if (j == i || j == (x - 1 - i)) {
                continue;
            }
            chars[j] = getCharMid_DataF(pointerLocation,userEnteredString);
        }
        for(int i=0;i<sizeof(chars)/sizeof(char);i++)
        {
            resultString = resultString  + chars[i];
        }
        resultString = resultString  + "\n";
    }
    return resultString;
}

//Prints to the file with the name given by the user.
void printToFile(string resultString,string nameOfTheFile)
{
 	ofstream myfile;
  	myfile.open (nameOfTheFile.c_str());
  	myfile << resultString;
  	myfile.close();
}

//Main function of the program
int main(int argc, char* argv[])
{
	//Initiating initial sets of test to check for valid inputs

	//Checking for proper number of inputs
	if(argc!=5)
	{
		std::cerr<<"ERROR : Please enter exact arguments\n";
		return 1;
	}


	int heightOfPolygon ;
	string shapeOfPolygon = argv[3];
	for(unsigned int i=0;i<shapeOfPolygon.size();i++)
	{
		shapeOfPolygon[i] = tolower(shapeOfPolygon[i]);
	}

	//Checking for proper input of the shape of polygon
	if(shapeOfPolygon.compare("isosceles_triangle")!=0 && shapeOfPolygon.compare("right_triangle")!=0 && shapeOfPolygon.compare("square")!=0 && shapeOfPolygon.compare("x_shape")!=0 && shapeOfPolygon.compare("parallelogram")!=0 && shapeOfPolygon.compare("trapezium")!=0 && shapeOfPolygon.compare("house")!=0)
	{
		cerr<< "ERROR : Enter correct expected shape of Polygon. \n";
		return 1;
	}

	string userEnteredString = argv[1];

	//Checking for user entered string to be non-empty
	if(userEnteredString.compare("")==0)
	{
		cerr<<"ERROR : Please enter an un-empty String\n";
	}

	string nameOfTheFile = argv[4];
	string resultString;
	std::istringstream iss( argv[2] );
	iss >> heightOfPolygon;

	//Checking for whether the entered height is a number
	if(iss.eof()==false)
	{
		cerr<<"ERROR : Height entered should be a number.\n";
		return 1;
	}


	if(shapeOfPolygon=="right_triangle")
	{
		if(heightOfPolygon>3)
		{	
			
			resultString = ProcessRightTriangle(heightOfPolygon,userEnteredString);
		}	
		else
		{
			cerr<<"ERROR : Wrong height for the polygon "<<shapeOfPolygon<<"\n";
			return 1;
		}
	}

	if(shapeOfPolygon=="square")
	{
		if(heightOfPolygon>2)
		{	
			resultString = ProcessSquare(heightOfPolygon,userEnteredString);
		}	
		else
		{
			cerr<<"ERROR : Wrong height for the polygon "<<shapeOfPolygon<<"\n";
			return 1;
		}
	}


	if(shapeOfPolygon=="isosceles_triangle")
	{
		
		if(heightOfPolygon>1)
		{	
			resultString = ProcessIsoscelesTriangle(heightOfPolygon,userEnteredString);
		}	
		else
		{
			cerr<<"ERROR : Wrong height for the polygon "<<shapeOfPolygon<<"\n";
			return 1;
		}
	}

	if(shapeOfPolygon=="parallelogram")
	{
		
		if(heightOfPolygon>2)
		{	
			resultString = ProcessParallelogram(heightOfPolygon,userEnteredString);
		}	
		else
		{
			cerr<<"ERROR : Wrong height for the polygon "<<shapeOfPolygon<<"\n";
			return 1;
		}
	}

	if(shapeOfPolygon=="trapezium")
	{
		
		if(heightOfPolygon>2)
		{	
			resultString = ProcessTrapezium(heightOfPolygon,userEnteredString);
		}	
		else
		{
			cerr<<"ERROR : Wrong height for the polygon "<<shapeOfPolygon<<"\n";
			return 1;
		}
	}

	if(shapeOfPolygon=="x_shape")
	{
		
		if(heightOfPolygon>2)
		{	
			resultString = ProcessXShape(heightOfPolygon,userEnteredString);
		}	
		else
		{
			cerr<<"ERROR : Wrong height for the polygon "<<shapeOfPolygon<<"\n";
			return 1;
		}
	}
	
	if(shapeOfPolygon=="house")
	{
		
		if(heightOfPolygon>2)
		{	
			resultString = ProcessHouse(heightOfPolygon,userEnteredString);
		}	
		else
		{
			cerr<<"ERROR : Wrong height for the polygon "<<shapeOfPolygon<<"\n";
			return 1;
		}
	}
	

	printToFile(resultString,nameOfTheFile);
	
	return 0;
}