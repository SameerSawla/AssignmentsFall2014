#include <vector>
class Scores
{
	public:
		//Accessors
		std::vector<int> getScoreVector(){ return scoreSheet;}
		int getScoreAtIndex(int i){return scoreSheet[i];}
		int getSize(){return scoreSheet.size();}
		bool isNull(){if(scoreSheet.size()==0){return true;}return false;}
		void display();

		//Modifier
		void push(int i){ scoreSheet.push_back(i);}
		void setNull(){scoreSheet.clear();}
	private:

		//Data Member
		std::vector<int> scoreSheet;
};