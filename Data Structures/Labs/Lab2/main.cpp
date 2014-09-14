#include<iostream>
#include<vector>
#include<algorithm>
#include "time.h"

using namespace std;

void printVector(vector<Time>& input)
{
 for(unsigned int i=0;i<input.size();i++)
 {
 	input[i].print();
 }
}

int main()
{
	Time one;
	Time two(13,61,61);
	// two.printAmPm();

	// one.setHour(5);
	// one.setMinute(4);
	// one.setSecond(2);
	// one.printAmPm();

	// one.setHour(0);
	// one.setMinute(0);
	// one.setSecond(0);
	// one.printAmPm();

	one.setHour(12);
	one.setMinute(0);
	one.setSecond(0);
	// one.printAmPm();

	Time three(0,0,0);
	Time four(12,30,0);

	vector<Time> timeVector;
	timeVector.push_back(two);
	timeVector.push_back(one);
	timeVector.push_back(three);
	timeVector.push_back(four);

	cout<<"Before Sorting : \n";
	printVector(timeVector);

	sort(timeVector.begin(),timeVector.end(),IsEarlierThan);

	cout<<"\nAfter Sorting : \n";
	printVector(timeVector);
	return 0;
}