
class PlayerGameDetails
{
	public:
		//Accessor
		std::string getPlayerName(){return player.getFirstName() + " " + player.getLastName();}
		Player getPlayer() const{return player;}
		int getNameSize(){return getPlayerName().size();}
		Scores getScores(){return scores;}
		std::vector<int> getCumulativeScores() const{return cumulativeScores;}
		void display();

		//Modifier
		void setPlayer(Player playerI){ player = playerI;}
		void setScores(Scores scoresI){ scores = scoresI;}
		void setcumulativeScores(std::vector<int> cumScoresInput){ for(unsigned int i=0;i<cumScoresInput.size();i++){cumulativeScores.push_back(cumScoresInput[i]);}}
	private:
		Player player;
		Scores scores;	
		std::vector<int> cumulativeScores;
};