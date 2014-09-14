#include <string>
#include <vector>
#include "player.h"
#include "scores.h"
#include "playergamedetails.h"

//Display the Player details and its scores
void PlayerGameDetails::display()
{
	player.display();
	scores.display();
}