#include<iostream>
#include<string>
#include<sstream>
#include "time.h"
using namespace std;

Time::Time()
{
	hour = 0 ;
	minute = 0;
	second = 0;
}

Time::Time(int h,int m,int s)
{
	hour = h;
	minute = m;
	second = s;
}

int Time::getHour() const
{
	return hour;
}

int Time::getMinute() const
{
	return minute;
}

int Time::getSecond() const
{
	return second;
}

void Time::setHour(int h)
{
	hour = h;
}

void Time::setMinute(int m)
{
	minute = m;
}

void Time::setSecond(int s)
{
	second = s;
}

void Time::print()
{
 cout<<hour<<":"<<minute<<":"<<second<<endl;
}

void Time::printAmPm()
{		
	string timePhase = "am";
	while(second>60)
	{
		second = second - 60;
		minute++;
	}

	while(minute>60)
	{
		minute = minute - 60;
		hour++;
	}

	while(hour>24)
	{
		hour = hour - 24;
	}
	if(hour>=12)
	{
	 timePhase = "pm";	
	}
	
	if(hour>12)
	{
		hour = hour - 12;
		
	}

	ostringstream oss;

    oss << hour;
    string hs  = oss.str();
    hs = (hour<10)?("0"+hs):hs; 
    oss.str("");
    
    oss << minute;
    string ms  = oss.str();
    ms = (minute<10)?("0"+ms):ms; 
    oss.str("");

    oss << second;
    string ss  = oss.str();	
	ss = (second<10)?("0"+ss):ss; 
	oss.str("");

	cout<<hs<<":"<<ms<<":"<<ss<<" "<<timePhase<<endl;
}

bool IsEarlierThan(const Time& t1,const Time& t2)
{	
	if(t1.getHour()!=t2.getHour())
	{
		return (t1.getHour()<t2.getHour())?true:false;
	}
	if(t1.getMinute()!=t2.getMinute())
	{
		return (t1.getMinute()<t2.getMinute())?true:false;
	}
	return (t1.getSecond()<t2.getSecond())?true:false;
	
}