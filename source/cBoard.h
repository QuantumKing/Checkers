
class cBoard
{

		int board[8][8]; /// red pieces == 1, black pieces == 2, no piece = 0.

	public:

		cBoard (void);

		void move (int i, int j, int d, int n); ///  d is the direction of the move: 0 = top left, 1 = top right, 2 = bottom left, 3 = bottom right. 
							///  n represents how many steps. i,j represents the coordinate to be moved.

		const int at (const int i, const int j) const;

		
		void possible_moves(int i, int j, int moves[4]) const;
		

};
