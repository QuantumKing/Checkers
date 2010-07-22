#include "c3DCheckers.h"

int round(float a)
{
	return int(a + 0.5f);
}

c3DCheckers::c3DCheckers(int W, int H, int ScreenFlags, int ScreenBPP) : c3DWindow(W, H, ScreenFlags | SDL_GL_DOUBLEBUFFER, ScreenBPP)
{ 
	SDL_Init(SDL_INIT_TIMER);

	current_time = 0.0f;
	last_time = 0.0f;
	delta_time = 0.0f;
 
	current_piece_moving = false;
	current_piece = -1;

	n_dead_red_pieces = 0; 
	n_dead_black_pieces = 0;

	z = -6.5f;	
	roll = 0.0f;
	pitch = 0.0f;
	heading = 60.0f;

	glLists::BuildLists();

	checker_board = new c3DCheckerBoard(0.0f,0.0f,0.0f);

	board = new cBoard();

	int k = 0;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(board->at(i,j)==1)
			{
				pieces[k] = new c3DCheckerPiece(-1.4f+j*0.4f,0.15f,-1.4f+i*0.4f);
				pieces[k]->setColor(1);
				k++;
			}
			else if(board->at(i,j)==2)
			{
				pieces[k] = new c3DCheckerPiece(-1.4f+j*0.4f,0.15f,-1.4f+i*0.4f);
				pieces[k]->setColor(2);
				k++;
			}
		}	
	}


	done = false;

	mmb_down = false;
	lmb_down = false;
}


void c3DCheckers::Execute (void)
{
	while(!done)
	{
		GetInput();
		Update();
		Render();
	}
}


void c3DCheckers::Update (void)
{
	current_time = SDL_GetTicks()/1000.0f;
			
	delta_time = current_time - last_time;

	last_time = current_time;

	if(current_piece_moving)
		move_piece (current_piece_i, current_piece_j, current_piece_moving_direction, current_piece_moving_steps);
}


void c3DCheckers::Render (void)
{
	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glTranslatef(0.0f,0.0f,z);

	glRotatef(roll,0.0f,0.0f,1.0f);
	glRotatef(pitch,0.0f,1.0f,0.0f);
	glRotatef(heading,1.0f,0.0f,0.0f);

	checker_board->draw();
	
	for(int i = 0; i < 24; ++i)
		pieces[i]->draw();

	SDL_GL_SwapBuffers();
	SDL_Delay(5);
}

void c3DCheckers::GetInput (void)
{
	Vector3D v;

	while(SDL_PollEvent(&event))
	{
	switch(event.type)
	{ 

		case SDL_QUIT:
			done = true;
			break;

		case SDL_KEYDOWN:

			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					done = true;
					break;

				case SDLK_f:
					toggle_fullscreen();

				default:
					break;
			}		
			break;

			case SDL_MOUSEBUTTONDOWN:

				switch(event.button.button)
				{
					case SDL_BUTTON_MIDDLE:
						mmb_down = true;
						break;

					case SDL_BUTTON_LEFT:
						if(current_piece_moving)
							break;

							current_piece = -1;

							lmb_down = true;
							v = GetOGLPos(event.motion.x,event.motion.y);

							for(int i = 0; i < 24; ++i)
							{
								if( pieces[i]->Vector3DIntersect(v) )
								{
									current_piece_i = round((v.z+1.4f)/0.4f);
									current_piece_j = round((v.x+1.4f)/0.4f);
									current_piece = i;
									break;			
								}
							}
							break;

					default:
						break;
				}
				break;

			case SDL_MOUSEMOTION:
				if(mmb_down)
				{
					pitch += 0.3f*event.motion.xrel;
					heading += 0.3f*event.motion.yrel;

					if(pitch >= 360.0f)
						pitch -= 360.0f;
					else if(pitch <= -360.0f)
						pitch += 360.0f;

					if(heading >= 360.0f)
						heading -= 360.0f;
					else if(heading <= -360.0f)
						heading += 360.0f;
				}

				if(lmb_down && !current_piece_moving && current_piece != -1)
				{
					v = GetOGLPos(event.motion.x,event.motion.y);

					float dx = v.x - pieces[current_piece]->X();
					float dz = v.z - pieces[current_piece]->Z();

					if( (dx >= 0.2f || dx <= -0.2f) && (dz >= 0.2f || dz <= -0.2f) )
					{
						int moves[4];
						board->possible_moves(current_piece_i,current_piece_j,moves);

						if( dx < 0.0f && dz < 0.0f ) 
						{
							current_piece_moving_direction = 0;
							current_piece_moving_steps = moves[0];
						}
						if( dx > 0.0f && dz < 0.0f )
						{
							current_piece_moving_direction = 1;
							current_piece_moving_steps = moves[1];
						}
						if( dx < 0.0f && dz > 0.0f )
						{
							current_piece_moving_direction = 2;
							current_piece_moving_steps = moves[2];
						}
						if( dx > 0.0f && dz > 0.0f )
						{
							current_piece_moving_direction = 3;
							current_piece_moving_steps = moves[3];
						}

						board->move(current_piece_i,current_piece_j,current_piece_moving_direction,current_piece_moving_steps); // update the cBoard board.

						current_piece_moving = true;
					}
				}
							
				break;


			case SDL_MOUSEBUTTONUP:

				switch(event.button.button)
				{
					case SDL_BUTTON_MIDDLE:
						mmb_down = false;
						break;

					case SDL_BUTTON_LEFT:
						lmb_down = false;
						board->new_turn();
						break;

					case SDL_BUTTON_WHEELUP:
						z += 0.3f;
						break;

					case SDL_BUTTON_WHEELDOWN:
						z -= 0.3f;
						break;

					default:
						break;
				}
				break;

			case SDL_VIDEORESIZE:

				resize( event.resize.w, event.resize.h );
				break;

			default:
		     		break;
		}
	}
}


void c3DCheckers::move_piece (int i, int j, int d, int n)
{
	if( d < 0 || d > 3 )
		return;

	int a = (d == 0 || d == 2 ? -1 : 1);
	int b = (d == 0 || d == 1 ? -1 : 1);


	if( n == 1 || n == 2 )
	{	
		c3DCheckerPiece *cp = pieces[current_piece];

		float q = (-1.4f+(a+j)*0.4f);

		if( n == 2 )
		{
			if((cp->X() > q && a > 0) || (cp->X() < q && a < 0)) // If the current piece is past the middle of where it is supposed to go.
			{
				cp->move_by( 2*a*delta_time , -0.004f , 2*b*delta_time );
			}
			else cp->move_by( 2*a*delta_time , 0.004f , 2*b*delta_time );

			q += a*0.4f;
		}
		else cp->move_by( a*delta_time , 0.0f , b*delta_time );


		if((cp->X() > q && a > 0) || (cp->X() < q && a < 0)) // If the current piece is past where it is supposed to go.
		{
			cp->move_to( q , 0.15f , -1.4f+(i+n*b)*0.4f );

			if( n == 2 )
			{
				q -= a*0.4f;
				Vector3D v( q , 0.15f , -1.4f+(i+b)*0.4f );

				for(int k = 0; k < 24; ++k)
				{
					if( pieces[k]->Vector3DIntersect(v) )
					{
						int c = pieces[k]->Color();
						bool red_piece = (c==1 || c==3);
						q = red_piece ? -1.8f : 1.8f;
						int& m = red_piece ? n_dead_red_pieces : n_dead_black_pieces;
						pieces[k]->move_to( -1.8f + 0.3f*m , 0.34f, q );
						m++;
						break;
					}
				}
			}

			current_piece_moving = false;
			current_piece_i += n*b;
			current_piece_j += n*a;

			if( cp->isKinged() ) return;

			if(board->at(current_piece_i,current_piece_j)==3)
			{
				cp->setKinged(true);
			}
			else if(board->at(current_piece_i,current_piece_j)==4)
			{
				cp->setKinged(true);
			}
		}
	}
	else current_piece_moving = false;
		
}	


Vector3D c3DCheckers::GetOGLPos(int x, int y) const
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	return Vector3D(posX, posY, posZ);
}

