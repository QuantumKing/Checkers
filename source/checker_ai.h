#include "cBoard.h"

class MoveSet;

extern int ai_color, player_color;

bool better_move_ai (cBoard *board, int color, MoveSet *move_set);


class MoveSet
{
		int move_set[12][2]; /// The set of directions and step sizes.
		int level; /// The number of the current step.
		int start_i, start_j; /// The coordinates of the first position where the moving starts.

	public:

		MoveSet (int pos_i, int pos_j)
		{
			for(int i = 0; i < 12; ++i)
			{
				for(int j = 0; j < 2; ++j)
					this->move_set[i][j] = 0;
			}
			level = 0;
			start_i = pos_i;
			start_j = pos_j;
		}

		MoveSet (void) {};

		int d (int k) const
		{
			return move_set[k][0];
		}

		int n (int k) const
		{
			return move_set[k][1];
		}

		void add_move (int d, int n)
		{
			move_set[level][0] = d;
			move_set[level][1] = n;
			level++;
		}

		void pop_move (void)
		{
			if(level < 1) return;

			move_set[--level][0] = 0;
			move_set[level][1] = 0;
		}
			
		int i (void) const
		{
			return start_i;
		}

		int j (void) const
		{
			return start_j;
		}
};
