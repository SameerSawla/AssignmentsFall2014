#include<iostream>
#include<string>
#include<sstream>
using namespace std;
int main()
{
	int h =9;
	int m=10;
	int s=2;
	ostringstream ss;

    ss << h;
    string hs  = ss.str();
    hs = (h<10)?("0"+hs):hs; 
    ss.str("");
    
    ss << m;
    string ms  = ss.str();
    ms = (m<10)?("0"+ms):ms; 
    ss.str("");

    ss << s;
    string ss2  = ss.str();	
	ss2 = (s<10)?("0"+ss2):ss2; 
	ss.str("");

	cout<<hs<<":"<<ms<<":"<<ss2<<" "<<endl;
	return 0;
}