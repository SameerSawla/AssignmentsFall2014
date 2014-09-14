#include<iostream>
#include<string>
using namespace std;
int main()
{	
		int heightOfPolygon = 15;
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
					string temp1((2*heightOfPolygon-3),' ');
					string temp2(2*i-1,' ');
					resultString = resultString + temp1 + temp2;
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
		string innerspaced(finalHeight-3,' ');
		if(i==heightOfPolygon-1)
		{
			resultString = resultString + spacedTwo;
			string starred(finalHeight-1,'*');
			resultString = resultString + starred + "\n";
			continue;
		}
		
		resultString = resultString + spacedTwo + "*";
		resultString = resultString + innerspaced + "*\n";

		}

		for(int i=0;i<=heightOfPolygon/2;i++)
		{
			int pathLength = (finalHeight+1)/3;
			string pathSpace1(pathLength+i,' ');
			string pathSpace2(pathLength,' ');
			resultString = resultString + pathSpace1+"*"+pathSpace2+"*\n";
		}
		cout<<resultString;
	return 0;
}