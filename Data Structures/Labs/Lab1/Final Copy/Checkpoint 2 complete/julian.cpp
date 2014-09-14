  //  This program converts a day and month within a given year to the
//  Julian day.

#include <iostream>


//  This is a constant array of integer values.  The array entry
//  associated with index i is the number of days in the ith month of
//  the year.  Since C++ array indices start at 0 and month counting
//  starts at 1, there are 13 locations in the array, and the
//  first location is given a default value of 0.
const int DaysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 
				31, 31, 30, 31, 30, 31 };

const int InputDays[10] = {1,2,3,4,5,6,7,8,9,10};

const int InputMonths[10] = {1,2,3,4,5,6,7,8,9,10};

int JulianDayArray[10];

//  Function returns true if the given year is a leap year and
//  returns false otherwise.
bool is_leap_year( int year )
{
  return (year % 4 == 0) && ( (year % 100 != 0) || (year % 400 == 0) );
}


//  Calculate and return the Julian day associated with the given
//  month and day of the year.
int julian_day( int month, int day, int year )
{
  int jday = 0;
  for ( unsigned int m=1; m<month; ++m )
    {
      jday += DaysInMonth[m];
      if ( m == 2 && is_leap_year(year))
      { ++jday;  // February 29th
      }
    }
  jday += day;
  return jday;
}


int main()
{

  for(unsigned int i=0;i<10;i++)
  {
    JulianDayArray[i] = julian_day(InputMonths[i],InputDays[i],2014);
  }

  std::cout<<"The julian days are as below :\n ";
  for(unsigned int i=0;i<10;i++)
  {
    std::cout<<JulianDayArray[i]<< std::endl;
  }
  return 0;
}
