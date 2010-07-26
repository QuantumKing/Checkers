
#include "c3DWindow.h"

#include "c3DCheckerBoard.h"
#include "c3DCheckerPiece.h"

#include "cBoard.h"
#include "checker_ai.h"

class c3DCheckers : public c3DWindow
{
	
		float current_time, last_time, delta_time;

		c3DCheckerBoard *checker_board;
		c3DCheckerPiece *pieces[24];

		int n_dead_red_pieces, n_dead_black_pieces;

		int current_piece; // The location of the current piece in pieces array.
		int current_piece_i, current_piece_j; // The location of the current piece on the board.
		int current_piece_moving_direction, current_piece_moving_steps;
		bool current_piece_moving;

		bool player_turn;

		int move_count;
		MoveSet opponent_moves;

		bool ai;

		cBoard *board;

		bool done;

		SDL_Event event;

		bool mmb_down, lmb_down;

		float z, pitch, heading;


		void move_piece (int i, int j, int d, int n);	///  d is the direction of the move: 0 = top left, 1 = top right, 2 = bottom left, 3 = bottom right. 
								///  n represents how many steps. i,j represents the coordinate to be moved.
		Vector3D GetOGLPos(int x, int y) const;

		void select_piece_at(Vector3D& v);


	public:
	
		c3DCheckers(int W, int H, int ScreenFlags, int ScreenBPP);

		void Execute (void);

		void Update (void);

		void Render (void);

		void GetInput (void);

};


