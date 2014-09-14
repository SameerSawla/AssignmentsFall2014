#include<iostream>
#include<vector>
using namespace std;
int main()
{
	vector<int> scores;
	
	scores.push_back(1);
	scores.push_back(2);

	for(unsigned int i=0;i<scores.size();i++)
	{
		cout<<scores[i]<<endl;
	}
	scores[1] = 100;
	cout<<"Edited values "<<endl;

	for(unsigned int i=0;i<scores.size();i++)
	{
		cout<<scores[i]<<endl;
	}

	/*Ways to initialize vectors*/
	vector<int> scores2(scores);
	for(unsigned int i=0;i<scores.size();i++)
	{
		cout<<scores2[i]<<endl;
	}	

	return 0;
}