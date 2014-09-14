class Time
{
 public:
 	//Constructor
 	Time();
 	Time(int h,int m,int s);
 	
 	//Accesors
 	int getHour() const;
 	int getMinute() const;
 	int getSecond() const;
 	void printAmPm();
 	void print();

 	//Modifiers
 	void setHour(int h);
 	void setMinute(int m);
 	void setSecond(int s);


 private:
 	int hour;
 	int minute;
 	int second;
};

bool IsEarlierThan(const Time& t1,const Time& t2);
