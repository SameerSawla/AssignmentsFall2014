/*
Header file for the Player Class
*/
class Player
{
	public:

		//Constructor
		Player(std::string fName,std::string lName);
		Player(){firstName =""; lastName="";};
		
		//Accessors
		std::string getFirstName(){ return firstName;}
		std::string getLastName(){ return lastName;}
		bool isNull(){if(firstName.empty() && lastName.empty()){return true;} return false;}
		void display();

		//Modifiers
		void setFirstName(std::string fName){firstName = fName;}
		void setLastName(std::string lName){lastName = lName;}
	private:
		//Data Members
		std::string firstName;
		std::string lastName;

};