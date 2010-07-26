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
	forced_jump = false;
	n_types[0] = 12;
	n_types[1] = 12;
	n_types[2] = 0;
	n_types[3] = 0;
}


int cBoard::number_of_type (int type) const
{
	return n_types[type-1];
}


bool cBoard::new_turn (void)		// returns false if the turn doesn't change.
{
	if(first || forced_jump) return false; 	// If the player hasn't moved yet, then it isn't time for a new turn.

	first = true;
	forced_jump = false;

	return true;
}


void cBoard::move (int i, int j, int d, int n)
{
	if( n <= 0 || n > 2 ) return;

	int a = (d == 0 || d == 2 ? -1 : 1);
	int b = (d == 0 || d == 1 ? -1 : 1);
 
	int p1 = i+n*b, p2 = j+n*a;

	if( n == 2 )
	{
		n_types[board[i+b][j+a]-1]--;

		board[i+b][j+a] = 0;
		board[p1][p2] = board[i][j];
		board[i][j] = 0;

		forced_jump = check_can_jump(p1,p2);

		if(forced_jump)
		{
			forced_jump_i = p1;
			forced_jump_j = p2;
		}
	}
	else if( n == 1 )
	{
		board[p1][p2] = board[i][j];
		board[i][j] = 0;
	}

	if(board[p1][p2] == 1 && p1 == 0)
	{
		board[p1][p2] = 3;
		n_types[2]++;
		forced_jump = false;			/// If you are kinged, your turn is over.
	}
	else if(board[p1][p2] == 2 && p1 == 7)
	{
		board[p1][p2] = 4;
		n_types[3]++;
		forced_jump = false;			/// If you are kinged, your turn is over.
	}

	first = false;
}


const int cBoard::at (const int i, const int j) const
{
	return board[i][j];
}


int cBoard::color_at (int i, int j) const
{
	if(board[i][j] == 0) return 0;

	return (board[i][j] == 1 || board[i][j] == 3 ? 1 : 2);	/// A color of 1 means red, 2 means black.
}


bool cBoard::possible_moves(int i, int j, int moves[4])		/// moves holds the number of steps for each possible move. I use d to index moves (top left is at index 0..).
								/// n = 0 means no move.
{
	moves[0] = 0; moves[1] = 0; moves[2] = 0; moves[3] = 0;

	if( board[i][j] == 0 )
		return false;

	if( !forced_jump && !first )				// Only allowed to make more than one move when forced to jump.
	{
		return false;
	}
	else if(!forced_jump && first)				// If this is the first move and you aren't (yet) forced to jump, check if you are.
	{
		forced_jump = check_forced_jump(board[i][j]);
	}
	else if(!first)						// If you are forced to jump, then you must use the same piece you had initially.
	{
		if(i != forced_jump_i || j != forced_jump_j)
			return false;
	}

	int e1 = (board[i][j] == 1 || board[i][j] == 3) ? 2 : 1;
	int e2 = e1 + 2;

	bool possible = false;

	if(board[i][j] != 2)
	{
		/// top left corner ( d = 0 )

		if(i > 0 && j > 0)
		{
			if( board[i-1][j-1] == 0 && !forced_jump )
			{
				moves[0] = 1;
				possible = true;
			}
			else if( i > 1 && j > 1 && (board[i-1][j-1] == e1 || board[i-1][j-1] == e2) )
			{
				if(board[i-2][j-2] == 0)
				{
					moves[0] = 2;
					possible = true;
				}
			}
		}

		/// top right corner ( d = 1 )

		if(i > 0 && j < 7)
		{
			if( board[i-1][j+1] == 0 && !forced_jump )
			{
				moves[1] = 1;
				possible = true;
			}
			else if( i > 1 && j < 6 && (board[i-1][j+1] == e1 || board[i-1][j+1] == e2) )
			{
				if(board[i-2][j+2] == 0)
				{
					moves[1] = 2;
					possible = true;
				}
			}
		}
	}

	if(board[i][j] != 1)
	{
		/// bottom left corner ( d = 2 )

		if(i < 7 && j > 0)
		{
			if( board[i+1][j-1] == 0 && !forced_jump )
			{
				moves[2] = 1;
				possible = true;
			}
			else if( i < 6 && j > 1 && (board[i+1][j-1] == e1 || board[i+1][j-1] == e2) )
			{
				if(board[i+2][j-2] == 0)
				{
					moves[2] = 2;
					possible = true;
				}
			}
		}

		/// bottom right corner ( d = 3 )

		if(i < 7 && j < 7)
		{
			if( board[i+1][j+1] == 0 && !forced_jump )
			{
				moves[3] = 1;
				possible = true;
			}
			else if( i < 6 && j < 6 && (board[i+1][j+1] == e1 || board[i+1][j+1] == e2) )
			{
				if(board[i+2][j+2] == 0)
				{
					moves[3] = 2;
					possible = true;
				}
			}
		}
	}
	return possible;
}


bool cBoard::check_can_jump (int i, int j) const
{
	int e1 = (board[i][j] == 1 || board[i][j] == 3) ? 2 : 1;
	int e2 = e1 + 2;

	if(board[i][j] != 2)
	{
		/// top left corner ( d = 0 )

		if(i > 1 && j > 1)
		{
			if(board[i-1][j-1] == e1 || board[i-1][j-1] == e2)
			{
				if(board[i-2][j-2]==0)
					return true;
			}
		}

		/// top right corner ( d = 1 )

		if(i > 1 && j < 6)
		{
			if(board[i-1][j+1] == e1 || board[i-1][j+1] == e2)
			{
				if(board[i-2][j+2]==0)
					return true;
			}
		}
	}

	if(board[i][j] != 1)
	{
		/// bottom left corner ( d = 2 )

		if(i < 6 && j > 1)
		{
			if(board[i+1][j-1] == e1 || board[i+1][j-1] == e2)
			{
				if(board[i+2][j-2]==0)
					return true;
			}
		}

		/// bottom right corner ( d = 3 )

		if(i < 6 && j < 6)
		{
			if(board[i+1][j+1] == e1 || board[i+1][j+1] == e2)
			{
				if(board[i+2][j+2]==0)
					return true;
			}
		}
	}
	return false;
}


bool cBoard::check_forced_jump (int color) const
{
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(board[i][j]==color || board[i][j]==color+2)
			{
				if(check_can_jump(i,j))
					return true;
			}
		}
	}
	return false;
}


int cBoard::at_direction_steps (int i, int j, int d, int n) const
{
	int a = (d == 0 || d == 2 ? -1 : 1);
	int b = (d == 0 || d == 1 ? -1 : 1);

	return board[i+b][j+a];
}

		
