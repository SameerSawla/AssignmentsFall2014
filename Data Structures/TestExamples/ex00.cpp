#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a="Kim";
	string b="Tom";
	cout<<a<<endl<<b<<endl;
	a[0] = b[0];
	cout<<a<<endl<<b<<endl;

	return 0;
}
