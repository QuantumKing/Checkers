#ifndef CBOARD_H
#define CBOARD_H

class cBoard
{

		int board[8][8]; /// red pieces == 1, black pieces == 2, no piece = 0.

		bool first;

		bool forced_jump;

		int forced_jump_i, forced_jump_j;

		int n_types[4];

	public:

		cBoard (void);

		void move (int i, int j, int d, int n); ///  d is the direction of the move: 0 = top left, 1 = top right, 2 = bottom left, 3 = bottom right. 
							///  n represents how many steps. i,j represents the coordinate to be moved.

		const int at (const int i, const int j) const;

		
		bool possible_moves (int i, int j, int moves[4]);	/// i,j represents the coordinate to be moved (maybe). 
									/// the moves are stored in moves (moves[i] represents n steps in direction ).
									/// returns true if there are ANY moves.

		bool new_turn (void);

		int color_at (int i, int j) const;

		
		bool check_can_jump (int i, int j) const;		/// checks if the current piece must make a jump.

		bool check_forced_jump (int color) const;		/// checks if any piece of a certain color must make a jump.
									/// a color of 1 means red, a color of 2 means black.

		int at_direction_steps (int i, int j, int d, int n) const;	/// Gets the piece when taking n steps from i,j in direction d.


		int number_of_type (int type) const;			/// Returns the number of pieces of a certain type: 1->red man, 2->black man, 3->red king, 4->black king.
		

};

#endif
