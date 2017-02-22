#ifndef BOARD_H
#define BOARD_H

#include "Checker.h"
#include <iostream>
#include <iomanip>

using std::ostream;
using std::endl;

const int rows = 5;
const int cols = 7;
const int diags = 17;
/**
This class represents the game board for our connect 4 game.  It is one row shorter than a typical connect four game, but
that's ok.  Our board is 7 columns wide by 5 rows tall.  The constants in the file can be used by you for declaring your
array and for loop constants etc.  The diags const was something I came up with to help me determine a diagonal win.  You
can use if it is helpful for you, otherwise, feel free to ignore it.
*/
class Board
{
private:
	/**
	This is the main game board.  It needs to be 2 dimensional
	*/
	Checker board[rows][cols];
	/**
	I use this to keep track of how many checkers have been placed.  I use this for checking draws.
	*/
	int checkerCount;
	/**
	This is a private method that I use in checking for wins.
	*/
	bool checkRow( int );
	/**
	Same as for checkRow and checkDiag, I use this in checking for wins.
	*/
	bool checkCol( int col );
	/**
	This is the same as the checkRow and checkCol methods.  I use this for checking for wins.
	*/
	bool checkDiag( int dia );//there are 18 locations where you can make a diagonol.  This number represents one of them.  I have numbered them from the top left starting with 0
public:
	/**
	This is the only constructor for the class.  It sets up the array and initializes everything to an empty checker, i.e. one with a "" for name and avatar.
	I can then use this fact of initialization when I go and check for wins.
	*/
	Board();

	/**
	This method does what you think.  It checks the rows, columns and diagonals for a winning condidtion.  It returns true if it finds one and false otherwise.
	@return True is a winning condition is found and false otherwise.
	*/
	bool win();
	/**
	This is similar to the win.  It checks for a draw.  There can only be a draw if all the spaces are filled.
	@return True if the game is in draw state and false otherwise
	*/
	bool draw();
	/**
	This drops a checker into the given row.  It should check to make sure that the given row is "good".  You also 
	need to make sure that the column is currently full of checkers.  If so, the drop is returned as false. Good is defined
	to be between 0 and 6. 
	@param checker - the Checker to be dropped
	@param column - an int that repesents the column to be dropped into
	@return True if the Checker could be dropped into the column and false otherwise.
	*/
	bool dropChecker( Checker checker, int column );
	/**
	This will return true if the game is in a win or draw state
	@return True if the game is in a win or draw state and false otherwise
	*/
	bool gameOver();
	/**
	This will display the board.  I will give more details on this to come.
	@param out - the ostream to use when displaying the board. 
	*/
	void displayBoard( ostream& out );
	/**
	This will reset the board to all blank checkers and reset the checker count back to 0.
	*/
	void resetBoard();
};

#endif
