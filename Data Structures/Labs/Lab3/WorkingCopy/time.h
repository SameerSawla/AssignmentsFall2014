#include <stdint.h>
class Time
{
 public:
 	//Constructor
 	Time();
 	Time(uintptr_t h,uintptr_t m,uintptr_t s);
 	
 	//Accesors
 	uintptr_t getHour() const;
 	uintptr_t getMinute() const;
 	uintptr_t getSecond() const;
 	void printAmPm();
 	void print();

 	//Modifiers
 	void setHour(uintptr_t h);
 	void setMinute(uintptr_t m);
 	void setSecond(uintptr_t s);


 private:
 	uintptr_t hour;
 	uintptr_t minute;
 	uintptr_t second;
};

bool IsEarlierThan(const Time& t1,const Time& t2);
