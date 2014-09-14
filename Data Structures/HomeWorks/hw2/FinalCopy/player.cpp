#include <string>
#include <iostream>
#include "player.h"

//Constructor
Player::Player(std::string fName,std::string lName)
{
	firstName = fName;
	lastName = lName;
}

//Display player's name
void Player::display()
{
	std::cout<<"\n"<<firstName<<" "<<lastName<<"\n";
}