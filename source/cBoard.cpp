#include "cBoard.h"

#include <iostream>
using namespace std;

cBoard::cBoard (void) ///  board[0][0] is at the top left corner of the checker board (at -x, -z). j is along x axis while i is along z.
{
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(j % 2 == 1 && (i == 0 || i == 2 || i == 6) )
			{
				if( i == 6 ) board[i][j] = 1;
				else board[i][j] = 2;
			}
			else if(j % 2 == 0 && (i == 1 || i == 5 || i == 7) )
			{
				if( i == 1 ) board[i][j] = 2;
				else board[i][j] = 1;
			}
			else board[i][j] = 0;
		}
	}
	first = true;
	red_turn = true;
}


void cBoard::new_turn (void)
{
	if(first) return; // If the player hasn't moved yet, then it isn't time for a new turn.

	first = true;
	red_turn = !red_turn;
}


void cBoard::move (int i, int j, int d, int n)
{
	if( n <= 0 || n > 2 ) return;

	int a = (d == 0 || d == 2 ? -1 : 1);
	int b = (d == 0 || d == 1 ? -1 : 1);
 
	int p1 = i+n*b, p2 = j+n*a;

	if( n == 2 )
	{
		board[i+b][j+a] = 0;
		board[p1][p2] = board[i][j];
		board[i][j] = 0;
	}
	else if( n == 1 )
	{
		board[p1][p2] = board[i][j];
		board[i][j] = 0;
	}

	if(board[p1][p2] == 1 && p1 == 0)
	{
		board[p1][p2] = 3;
	}
	else if(board[p1][p2] == 2 && p1 == 7)
	{
		board[p1][p2] = 4;
	}

	first = false;
}


const int cBoard::at (const int i, const int j) const
{
	return board[i][j];
}


void cBoard::possible_moves(int i, int j, int moves[4]) const	/// moves holds the number of steps for each possible move. I use d to index moves (top left is at index 0..).
								/// n = 0 means no move.
{
	moves[0] = 0; moves[1] = 0; moves[2] = 0; moves[3] = 0;

	if( board[i][j] == 0 )
		return;

	bool red = (board[i][j] == 1 || board[i][j] == 3);

	if((red && !red_turn) || (!red && red_turn))		// If the piece is red and it isn't the red turn, then return. Same for black pieces.
		return;

	int e1 = red ? 2 : 1;
	int e2 = e1 + 2;

	if(board[i][j] != 2)
	{
		/// top left corner ( d = 0 )

		if(i > 0 && j > 0)
		{
			if( board[i-1][j-1] == 0 && first )
			{
				moves[0] = 1;
			}
			else if( i > 1 && j > 1 && (board[i-1][j-1] == e1 || board[i-1][j-1] == e2) )
			{
				if(board[i-2][j-2] == 0)
					moves[0] = 2;
			}
		}

		/// top right corner ( d = 1 )

		if(i > 0 && j < 7)
		{
			if( board[i-1][j+1] == 0 && first )
			{
				moves[1] = 1;
			}
			else if( i > 1 && j < 6 && (board[i-1][j+1] == e1 || board[i-1][j+1] == e2) )
			{
				if(board[i-2][j+2] == 0)
					moves[1] = 2;
			}
		}
	}

	if(board[i][j] != 1)
	{
		/// bottom left corner ( d = 2 )

		if(i < 7 && j > 0)
		{
			if( board[i+1][j-1] == 0 && first )
			{
				moves[2] = 1;
			}
			else if( i < 6 && j > 1 && (board[i+1][j-1] == e1 || board[i+1][j-1] == e2) )
			{
				if(board[i+2][j-2] == 0)
					moves[2] = 2;
			}
		}

		/// bottom right corner ( d = 3 )

		if(i < 7 && j < 7)
		{
			if( board[i+1][j+1] == 0 && first )
			{
				moves[3] = 1;
			}
			else if( i < 6 && j < 6 && (board[i+1][j+1] == e1 || board[i+1][j+1] == e2) )
			{
				if(board[i+2][j+2] == 0)
					moves[3] = 2;
			}
		}
	}
}




		
