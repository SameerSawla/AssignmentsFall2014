#include<iostream>

void compute_squares(int a[],int b[],unsigned int &n)
{
	int *traverse;
	int *traverse2;
	for(traverse=a,traverse2=b;traverse<a+n;traverse++,traverse2++)
	{
		*traverse2 = *traverse * *traverse;
	}
	for(traverse=b;traverse<b+n;traverse++)
	{
		std::cout<<*traverse<<" ";
	}
	std::cout<<"\n";
}

int main()
{
	int a[5] = {1,2,3,4,5};
	int b[5];
	unsigned int n=5;
	std::cout<<"Before compute_squares\n";
	std::cout<<"contents of a \n";
	for(unsigned int i=0;i<n;i++)
	{
		std::cout<<a[i]<<" ";
	}

	std::cout<<"\ncontents of b \n";
	for(unsigned int i=0;i<n;i++)
	{
		std::cout<<b[i]<<" ";
	}
	std::cout<<"\n";
	compute_squares(a,b,n);

	std::cout<<"\n\nAfter compute_squares\n";
	std::cout<<"changed contents of a \n";
	for(unsigned int i=0;i<n;i++)
	{
		std::cout<<a[i]<<" ";
	}

	std::cout<<"\nchanged contents of b \n";
	for(unsigned int i=0;i<n;i++)
	{
		std::cout<<b[i]<<" ";
	}
	std::cout<<"\n";

}