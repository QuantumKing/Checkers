#include "checker_ai.h"
#include <iostream>
#include <vector>

using namespace std;

#define MAX_DEPTH 4

int best_worst, count;
MoveSet best_moves, possible_moves;

vector<int> nodes, dummy[MAX_DEPTH-1];


//int analyse_board (cBoard board

void recurse_better_move_ai (int depth, int num_moves, cBoard board, int color, int pos_i, int pos_j, MoveSet move_set, int& score);

bool better_move_ai (cBoard *board, int color, MoveSet *move_set, int score);

void sum_move_score (int depth, cBoard *board, int color, int score);


void recurse_better_move_ai (int depth, int num_moves, cBoard board, int color, int pos_i, int pos_j, MoveSet move_set, int& score)
{	
	count++;
		
	int d = move_set.d(num_moves-1);
	int n = move_set.n(num_moves-1);	

	int player_kings = board.number_of_type(player_color+2);
	int player_men = board.number_of_type(player_color);
	int ai_kings = board.number_of_type(ai_color+2);
	int ai_men = board.number_of_type(ai_color);

	board.move(pos_i,pos_j,d,n);

	score += 3*(board.number_of_type(ai_color+2) - ai_kings);
	score -= 3*(board.number_of_type(player_color+2) - player_kings);
	score += (board.number_of_type(ai_color) - ai_men);
	score -= (board.number_of_type(player_color) - player_men);

	pos_i += (d == 0 || d == 1 ? -n : n);
	pos_j += (d == 0 || d == 2 ? -n : n);

	int moves[4];

	if(!board.possible_moves(pos_i,pos_j,moves))
	{
		if(depth == MAX_DEPTH)
		{
			return;
		}
		else if(depth == 0)
		{
			possible_moves = move_set;
		}

		board.new_turn();
		sum_move_score (depth+1, &board, (color==ai_color?player_color:ai_color), score);

		return;
	}

	for(int k = 0; k < 4; ++k)
	{
		if( moves[k] > 0 )
		{
			move_set.add_move(k,moves[k]);

			recurse_better_move_ai (depth, num_moves+1, board, color, pos_i, pos_j, move_set, score);

			move_set.pop_move();
		}
	}	
}


bool better_move_ai (cBoard *board, int color, MoveSet *move_set)
{
	int moves[4];

	bool found_move = false;

	best_worst = -100;

	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(board->color_at(i,j) != color)
				continue;

			if(!board->possible_moves(i,j,moves))
				continue;

			found_move = true;

			MoveSet m(i,j);

			for(int k = 0; k < 4; ++k)
			{
				if( moves[k] > 0 )
				{
					//std::cout << i << " " << j << std::endl;

					m.add_move(k,moves[k]);

					int score = 0;
					count = 0;
					recurse_better_move_ai (0, 1, *board, color, i, j, m, score);

					cout << count << endl;
					int min = nodes[0];
					for(unsigned int i = 0; i < nodes.size(); ++i)
					{
						if( nodes[i] < min )
							min = nodes[i];
					}
					//cout << min << endl;
					if( min > best_worst )
					{
						best_moves = possible_moves;
						best_worst = min;
						//cout << best_worst << endl;
					}

					nodes.clear();

					m.pop_move();
				}
			}
		}
	}

	std::cout << std::endl;
	*move_set = best_moves;

	return found_move;
}


void sum_move_score (int depth, cBoard *board, int color, int score)
{
	int moves[4];

	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(board->color_at(i,j) != color)
				continue;

			if(!board->possible_moves(i,j,moves))
				continue;
	
			MoveSet m(i,j);

			for(int k = 0; k < 4; ++k)
			{
				if( moves[k] > 0 )
				{
					m.add_move(k,moves[k]);

					int s = score;

					recurse_better_move_ai (depth, 1, *board, color, i, j, m, s);

					if( depth == MAX_DEPTH )
					{
						dummy[0].push_back(s);
					}
					else
					{
						int j = MAX_DEPTH-depth-1;
						int m = dummy[j][0];
						for(unsigned int i = 0; i < dummy[j].size(); ++i)
						{
							if( j % 2 == 0 )
							{
								if( dummy[j][i] > m )
									m = dummy[j][i];
							}
							else
							{
								if( dummy[j][i] < m )
									m = dummy[j][i];
							}							
							//cout << dummy2[i] << " ";
						}
						//cout << endl;
						if( depth == 1 )
							nodes.push_back(m);
						else
							dummy[j+1].push_back(m);

						dummy[j].clear();
					}

					m.pop_move();
				}
			}
		}
	}
}







