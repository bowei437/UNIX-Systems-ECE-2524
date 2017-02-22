#include "Game.h"

Game::Game()
{
	theBoard.resetBoard();
}
/*
Ok...let's firgure out input:
Player 1
Name: <name>
Avatar: <avatar>
Player 2
Name: <name>
Avatar: <avatar>
Moves
display board
drop in <number> - <number> is 1-7 and represents a column, it's off by 1 from the actual column
*/
void Game::playGame( istream &player1, istream &player2, ostream& out )
{
	string name1, name2, avatar1, avatar2;
	string command;
	enum whosTurn { p1, p2 };
	whosTurn who = p1;
	int column;
	player1.ignore( 100, ':' );
	getline( player1, name1 );
	player1.ignore( 100, ':' );
	player1 >> avatar1;
	player2.ignore( 100, ':' );
	getline( player2, name2 );
	player2.ignore( 100, ':' );
	player2 >> avatar2;


	this->player1 = name1;
	this->player2 = name2;
	
	std::cout << "P1 Name: " << this->player1 << endl << "P1 Avatar: " << avatar1 << endl;
	std::cout << "P2 Name: " << this->player2 << endl << "P2 Avatar: " << avatar2 << endl;
	
	while( !theBoard.gameOver() && ( !player1.fail() || !player2.fail()  )  )
	{
		switch ( who )
		{
			case p1:
			player1 >> command;
			std::cout << "****P1 command " << command;
			if ( command == "display" )
			{
				player1 >> command;
				std::cout << " " << command <<endl;
				theBoard.displayBoard( out );
			}
			else if ( command == "drop" )
			{
				player1 >> command;
				player1 >> column;
				std::cout << " " << command << " " << column << endl;
				if ( theBoard.dropChecker(Checker( this->player1, avatar1), column-1 ) )
					who = p2;
			}
			break;
			case p2:
			player2 >> command;
			std::cout << "####P2 command " << command;
			if ( command == "display" )
			{
				player2 >> command;
				std::cout << " " << command <<endl;
				theBoard.displayBoard( out );
			}
			else if ( command == "drop" )
			{
				player2 >> command;
				player2 >> column;
				std::cout << " " << command << " " << column << endl;
				if ( theBoard.dropChecker(Checker( this->player2, avatar2), column-1 ) )
					who = p1;
			}
			break;
		}
	}
	bool winGame = theBoard.win();
	bool drawGame = theBoard.draw();
	theBoard.displayBoard( out );
	if ( winGame )
	{
		out << "Game over: ";
		switch( who )
		{
		case p1:
		out << this->player2 << " won" << endl;
		break;
		case p2:
		out << this->player1 << " won" << endl;
		break;
		}
	}
	if ( drawGame )
	{
		out << "Game over: Draw game" << endl;
	}
}
