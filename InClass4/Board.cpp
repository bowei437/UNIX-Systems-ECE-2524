#include "Board.h"

Board::Board()
{
	checkerCount = 0;
	Checker blank( "", "" );
	for ( int row=0; row<rows; row++ )
	{
		for ( int col=0; col<cols; col++ )
		{
			board[row][col] = blank;
		}
	}
}

bool Board::dropChecker( Checker checker, int column )
{
	bool dropped = false;
	Checker blank;
	if ( column < cols and column >= 0 )
	{
		for ( int row=rows-1; row>=0 && !dropped; row-- )
		{
			if ( board[row][column] == blank )
			{
//			std::cout << "Found row: " << row << endl;
				board[row][column] = checker;
				dropped = true;
				checkerCount++;
			}
		}
	}
	return dropped;
}
bool Board::win()
{
	bool winCheck = false;
	bool rowCheck = false;
	bool colCheck = false;
	bool diagCheck = false;
	for ( int i=0; i<rows; i++ )
	{
		rowCheck = rowCheck || checkRow( i );
	}
	for ( int i=0; i<cols; i++ )
	{
		colCheck = colCheck || checkCol( i );
	}
	for ( int i=0; i< diags; i++ )
	{
		diagCheck = diagCheck || checkDiag( i );
	}
	winCheck = rowCheck || colCheck || diagCheck;
	return winCheck;
}
bool Board::draw()
{
	bool drawCheck = false;
	if ( checkerCount == rows*cols )
	{
		drawCheck = !win();
	}
	return drawCheck;
}
bool Board::gameOver()
{
	return win() || draw();
}
bool Board::checkCol( int col )
{
	bool fourInARow = false;
	if ( col >= 0 && col < cols )
	{
		bool topFour, bottomFour;
		Checker blank;
		bool sub1, sub2, sub3, sub4;
		sub1 = board[0][col] == board[1][col];
		sub2 = board[1][col] == board[2][col];
		sub3 = board[2][col] == board[3][col];
		sub4 = (board[0][col]==blank || board[1][col]==blank || board[2][col]==blank || board[3][col]==blank );
		topFour = sub1 && sub2 && sub3 && !sub4;
		topFour = ((board[0][col] == board[1][col] && 
			  board[1][col] == board[2][col] && 
			  board[2][col] == board[3][col] ) && 
			  !(board[0][col]==blank || board[1][col]==blank || board[2][col]==blank || board[3][col]==blank ));
		sub1 = board[1][col] == board[2][col];
		sub2 = board[2][col] == board[3][col];
		sub3 = board[3][col] == board[4][col];
		sub4 = (board[4][col]==blank || board[1][col]==blank || board[2][col]==blank || board[3][col]==blank );
		bottomFour = sub1 && sub2 && sub3 && !sub4;
	//	bottomFour = ((board[1][col] == board[2][col] && 
	//		     board[2][col] == board[3][col] && 
	//		     board[3][col] == board[4][col] ) && 
	//		     !(board[4][col]==blank || board[1][col]==blank || board[2][col]==blank || board[3][col]==blank ));
		fourInARow = topFour || bottomFour;
	}
	return fourInARow;
}
bool Board::checkRow( int row )
{
	bool fourInARow = false;
	if ( row >= 0 && row < rows )
	{
		bool leftFour, leftMidFour, rightMidFour, rightFour;
		bool sub1, sub2, sub3, sub4;
		Checker blank;
		sub1 = board[row][0] == board[row][1];
		sub2 = board[row][1] == board[row][2];
		sub3 = board[row][2] == board[row][3];
		sub4 = (board[row][0]==blank || board[row][1]==blank || board[row][2]==blank || board[row][3]==blank );
		leftFour = sub1 && sub2 && sub3 && !sub4;
//		leftFour = board[row][0] == board[row][1] && 
//			   board[row][1] == board[row][2] && 
//			   board[row][2] == board[row][3] && 
//			   !(board[row][0]==blank || board[row][1]==blank || board[row][2]==blank || board[row][3]==blank );
		sub1 = board[row][1] == board[row][2];
	      	sub2 = board[row][2] == board[row][3];
		sub3 = board[row][3] == board[row][4];
		sub4 = (board[row][4]==blank || board[row][1]==blank || board[row][2]==blank || board[row][3]==blank );
		leftMidFour = sub1 && sub2 && sub3 && !sub4;
//		leftMidFour = board[row][1] == board[row][2] && 
//			      board[row][2] == board[row][3] && 
//			      board[row][3] == board[row][4] && 
//			      !(board[row][4]==blank || board[row][1]==blank || board[row][2]==blank || board[row][3]==blank );
		sub1 = board[row][2] == board[row][3];
	        sub2 = board[row][3] == board[row][4];
		sub3 = board[row][4] == board[row][5];
		sub4 = (board[row][5]==blank || board[row][4]==blank || board[row][2]==blank || board[row][3]==blank );
		rightMidFour = sub1 && sub2 && sub3 && !sub4;
//		rightMidFour = board[row][2] == board[row][3] && 
//			       board[row][3] == board[row][4] && 
//			       board[row][4] == board[row][5] && 
//			       !(board[row][5]==blank || board[row][4]==blank || board[row][2]==blank || board[row][3]==blank );
		sub1 = board[row][3] == board[row][4];
		sub2 = board[row][4] == board[row][5];
		sub3 = board[row][5] == board[row][6];
		sub4 = (board[row][6]==blank || board[row][5]==blank || board[row][4]==blank || board[row][3]==blank );
		rightFour = sub1 && sub2 && sub3 && !sub4;
//		rightFour = board[row][3] == board[row][4] && 
//			    board[row][4] == board[row][5] && 
//			    board[row][5] == board[row][6] && 
//			    !(board[row][6]==blank || board[row][5]==blank || board[row][4]==blank || board[row][3]==blank );

		fourInARow = leftFour || leftMidFour || rightMidFour || rightFour;
	}
	return fourInARow;
}
bool Board::checkDiag( int dia )
{
	bool fourInARow = false;
	Checker blank;
	if ( dia >=0 && dia <18 )
	{
		int row, col;
		if ( (dia < 4) || (dia > 7 && dia < 13) || (dia == 17) || ( dia == 8 ) )
		{
			if ( dia < 4 )
			{
				row = 0;
				col = dia;
			}
			else if ( dia < 13 && dia > 8 )
			{
				row = 1;
				col = 12 - dia;
			}
			else if ( dia == 8 )
			{
				row = 0;
				col = 3;
			}
			if ( ! ( board[row][col] == blank ) )
			{
				int r[4];
				int c[4];
				for ( int i=row, j=col, rc=0, cc=0; i<row+4 && j<col+4; i++, j++, rc++, cc++ )
				{
					r[rc] = i;
					c[cc] = j;
				}
				bool sub1, sub2, sub3, sub4;
				sub1 = board[r[0]][c[0]] == board[r[1]][c[1]];
				sub2 = board[r[1]][c[1]] == board[r[2]][c[2]];
				sub3 = board[r[2]][c[2]] == board[r[3]][c[3]];
				sub4 = (board[r[0]][c[0]] == blank || board[r[1]][c[1]] == blank || board[r[2]][c[2]] == blank || board[r[3]][c[3]] == blank );
//					fourInARow = fourInARow || ( (board[i][j] == board[i+1][j+1]) && !(board[i][j] == blank) );
				fourInARow = sub1 && sub2 && sub3 && !sub4;
			}
		}
		else
		{
			if ( dia > 2 && dia < 7 )
			{
				row = 0;
				col = dia;
			}
			else if ( dia > 11 && dia < 16 )
			{
				row = 1;
				col = dia - ( 6 + ( 2 * ( dia-12 ) ) );
			}
			else if ( dia == 7 )
			{
				row = 1;
				col = 6;
			}
			else if ( dia == 16 )
			{
				row = 0;
				col = 3;
			}
			if ( ! ( board[row][col] == blank ) )
			{
				int r[4];
				int c[4];
			 	for ( int i=row, j=col, rc=0, cc=0; i<row+4 && j>col-4; i++, j--, rc++, cc++ )
				{
					r[rc] = i;
					c[cc] = j;
				}
				bool sub1, sub2, sub3, sub4;
				sub1 = board[r[0]][c[0]] == board[r[1]][c[1]];
				sub2 = board[r[1]][c[1]] == board[r[2]][c[2]];
				sub3 = board[r[2]][c[2]] == board[r[3]][c[3]];
				sub4 = (board[r[0]][c[0]] == blank || board[r[1]][c[1]] == blank || board[r[2]][c[2]] == blank || board[r[3]][c[3]] == blank );
//					fourInARow = fourInARow || ( (board[i][j] == board[i+1][j+1]) && !(board[i][j] == blank) );
				fourInARow = sub1 && sub2 && sub3 && !sub4;
			}
		}
	}
	return fourInARow;
}
void Board::displayBoard( ostream& out )
{
	for ( int i=0; i<cols*2+1;i++)
		out << "-";
	out << endl;
	for ( int row=0; row<rows; row++ )
	{
		out << "|";
		for ( int col=0; col<cols; col++ )
		{
			out << std::setw(1) <<  board[row][col].getAvatar() << "|";
		}
		out << endl;
		for ( int i=0; i<cols*2+1;i++)
			out << "-";
		out << endl;
	}
}

void Board::resetBoard()
{
	checkerCount = 0;
	Checker blank;
	for ( int row=0; row<rows; row++ )
	{
		for ( int col=0; col<cols; col++ )
		{
			board[row][col] = blank;
		}
	}
}
