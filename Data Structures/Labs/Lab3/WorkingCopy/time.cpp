#include<iostream>
#include<string>
#include<sstream>
#include <stdint.h>
#include "time.h"
using namespace std;

Time::Time()
{
	hour = 0 ;
	minute = 0;
	second = 0;
}

Time::Time(uintptr_t h,uintptr_t m,uintptr_t s)
{
	hour = h;
	minute = m;
	second = s;
}

uintptr_t Time::getHour() const
{
	return hour;
}

uintptr_t Time::getMinute() const
{
	return minute;
}

uintptr_t Time::getSecond() const
{
	return second;
}

void Time::setHour(uintptr_t h)
{
	hour = h;
}

void Time::setMinute(uintptr_t m)
{
	minute = m;
}

void Time::setSecond(uintptr_t s)
{
	second = s;
}

// void Time::print()
// {
//  cout<<hour<<":"<<minute<<":"<<second<<endl;
// }

// void Time::printAmPm()
// {		
// 	string timePhase = "am";
// 	while(second>60)
// 	{
// 		second = second - 60;
// 		minute++;
// 	}

// 	while(minute>60)
// 	{
// 		minute = minute - 60;
// 		hour++;
// 	}

// 	while(hour>24)
// 	{
// 		hour = hour - 24;
// 	}
// 	if(hour>=12)
// 	{
// 	 timePhase = "pm";	
// 	}
	
// 	if(hour>12)
// 	{
// 		hour = hour - 12;
		
// 	}

// 	ostringstream oss;

//     oss << hour;
//     string hs  = oss.str();
//     hs = (hour<10)?("0"+hs):hs; 
//     oss.str("");
    
//     oss << minute;
//     string ms  = oss.str();
//     ms = (minute<10)?("0"+ms):ms; 
//     oss.str("");

//     oss << second;
//     string ss  = oss.str();	
// 	ss = (second<10)?("0"+ss):ss; 
// 	oss.str("");

// 	cout<<hs<<":"<<ms<<":"<<ss<<" "<<timePhase<<endl;
// }

// bool IsEarlierThan(const Time& t1,const Time& t2)
// {	
// 	if(t1.getHour()!=t2.getHour())
// 	{
// 		return (t1.getHour()<t2.getHour())?true:false;
// 	}
// 	if(t1.getMinute()!=t2.getMinute())
// 	{
// 		return (t1.getMinute()<t2.getMinute())?true:false;
// 	}
// 	return (t1.getSecond()<t2.getSecond())?true:false;
	
// }