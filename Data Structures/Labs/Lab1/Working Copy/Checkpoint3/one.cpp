#include<iostream>

int main()
{
	int input;
	std::cout<<"Enter the number of float values to be inserted : ";
	std::cin>>input;

	float inputArray[input],sum, avg;

	std::cout<<"Enter the float values : ";
	for(unsigned int i=0;i<input;i++)
	{
		std::cin>>inputArray[i];
	}

	for(unsigned int i=0;i<input;i++)
	{
		sum = sum + inputArray[i];
	}
	
	avg = (float)sum/input;
	std::cout<<std::fixed<<avg<<"\t";

	for(unsigned int i=0;i<input;i++)
	{	
		float temp = inputArray[i];
		if(temp>avg)// inputArray[i] > avg
		{
			std::cout<<temp<<" "; //inputArray[i]
		}
	}
	std::cout<<std::endl;
	return 0;
}