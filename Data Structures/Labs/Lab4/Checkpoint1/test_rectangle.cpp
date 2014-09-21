#include<iostream>
#include<vector>
#include "Point2D.h"
#include "Rectangle.h"

using namespace std;

int main()
{
	Point2D one(0,0);
	Point2D two(2,2);

	Rectangle r1(one,two);
	print_rectangle(r1);

	Point2D three(1,1);
	Point2D four(-1,-1);

	Rectangle r2(three,four);
	print_rectangle(r2);

	if(r2.is_point_within(two))
	{
		cout<<"("<<two.x()<<","<<two.y()<<") is present in the rectangle";
	}
	else
	{
		cout<<"("<<two.x()<<","<<two.y()<<") is not present in the rectangle";
	}

	if(r1.is_point_within(two))
	{
		cout<<"("<<two.x()<<","<<two.y()<<") is present in the rectangle";
	}
	else
	{
		cout<<"("<<two.x()<<","<<two.y()<<") is not present in the rectangle";
	}
	return 0;

}