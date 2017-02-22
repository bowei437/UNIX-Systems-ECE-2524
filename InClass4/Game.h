#ifndef GAME_H
#define GAME_H

#include "Checker.h"
#include "Board.h"
#include <string>
#include <iostream>

using std::istream;
using std::ostream;
using std::string;
/**
This is the class that allows us to play the game.  It will take two input streams, one for each player, and an output
stream for displaying the board and who won.
*/
class Game
{
private:
	/**
	The name of the first player
	*/
	string player1;
	/**
	The name of the second player
	*/
	string player2;
	/**
	The Board
	*/
	Board theBoard;
public:
	/**
	The constructor
	*/
	Game();
	/**
	This will play the game.  This method will be described in the project description.
	*/
	void playGame( istream &player1, istream &player2, ostream& out );
};

#endif
