#include "3Ddefs.h"

namespace glLists
{

	GLuint textures[6];
	GLuint checker_board_rest;
	GLuint checker_board_top;
	GLuint checker_piece_rest;
	GLuint checker_piece_top;

void BuildLists (void)
{
	Texture t;

	t = Load2DTexture("pics/checkers_sides.bmp");
	textures[0] = t.t;

	t = Load2DTexture("pics/checker_board.bmp");
	textures[1] = t.t;

	t = Load2DTexture("pics/red_checker.bmp");
	textures[2] = t.t;

	t = Load2DTexture("pics/black_checker.bmp");
	textures[3] = t.t;

	t = Load2DTexture("pics/king_red.bmp");
	textures[4] = t.t;

	t = Load2DTexture("pics/king_black.bmp");
	textures[5] = t.t;


	checker_board_rest = glGenLists(3); 			// Building three lists.


	glNewList(checker_board_rest,GL_COMPILE);			// New Compiled 3d_checker_board Display List

		glBegin(GL_QUAD_STRIP);

			// Front Face
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -0.2f,  2.0f);
			glTexCoord2f(0.0f, 0.25f); glVertex3f(-2.0f,  0.3f,  2.0f);

			glTexCoord2f(0.25f, 0.0f); glVertex3f( 2.0f, -0.2f,  2.0f);
			glTexCoord2f(0.25f, 0.25f); glVertex3f( 2.0f,  0.3f,  2.0f);

			// Right face
			glNormal3f( 1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.5f, 0.0f); glVertex3f( 2.0f, -0.2f, -2.0f);
			glTexCoord2f(0.5f, 0.25f); glVertex3f( 2.0f,  0.3f, -2.0f);

			// Back Face
			glNormal3f( 0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.75f, 0.0f); glVertex3f(-2.0f, -0.2f, -2.0f);
			glTexCoord2f(0.75f, 0.25f); glVertex3f(-2.0f,  0.3f, -2.0f);

			// Left Face
			glNormal3f( -1.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -0.2f,  2.0f);
			glTexCoord2f(1.0f, 0.25f); glVertex3f(-2.0f,  0.3f,  2.0f);

		glEnd();

		glBegin(GL_QUAD_STRIP);

			// Top part
			glNormal3f( 0.0f, 1.0f, 0.0f);
			
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f,  0.3f,  2.0f);
			glTexCoord2f(0.0f, 0.25f); glVertex3f(-1.6f,  0.3f,  1.6f);

			glTexCoord2f(0.25f, 0.0f); glVertex3f( 2.0f,  0.3f,  2.0f);
			glTexCoord2f(0.25f, 0.25f); glVertex3f( 1.6f,  0.3f,  1.6f);

			glTexCoord2f(0.5f, 0.0f); glVertex3f( 2.0f,  0.3f, -2.0f);
			glTexCoord2f(0.5f, 0.25f); glVertex3f( 1.6f,  0.3f, -1.6f);

			glTexCoord2f(0.75f, 0.0f); glVertex3f(-2.0f,  0.3f, -2.0f);
			glTexCoord2f(0.75f, 0.25f); glVertex3f(-1.6f,  0.3f, -1.6f);

			glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f,  0.3f,  2.0f);
			glTexCoord2f(1.0f, 0.25f); glVertex3f(-1.6f,  0.3f,  1.6f);

		glEnd();

		glBegin(GL_QUAD_STRIP);

			// Inside part

			glNormal3f( 0.0f, 0.0f, -1.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.6f,  0.3f,  1.6f);
			glTexCoord2f(0.0f, 0.25f); glVertex3f(-1.6f,  0.1f,  1.6f);

			glTexCoord2f(0.25f, 0.0f); glVertex3f( 1.6f,  0.3f,  1.6f);
			glTexCoord2f(0.25f, 0.25f); glVertex3f( 1.6f,  0.1f,  1.6f);

			glNormal3f( -1.0f, 0.0f, 0.0f);

			glTexCoord2f(0.5f, 0.0f); glVertex3f( 1.6f,  0.3f, -1.6f);
			glTexCoord2f(0.5f, 0.25f); glVertex3f( 1.6f,  0.1f, -1.6f);

			glNormal3f( 0.0f, 0.0f, 1.0f);

			glTexCoord2f(0.75f, 0.0f); glVertex3f(-1.6f,  0.3f, -1.6f);
			glTexCoord2f(0.75f, 0.25f); glVertex3f(-1.6f,  0.1f, -1.6f);

			glNormal3f( 1.0f, 0.0f, 0.0f);

			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.6f,  0.3f,  1.6f);
			glTexCoord2f(1.0f, 0.25f); glVertex3f(-1.6f,  0.1f,  1.6f);

		glEnd();

		glBegin(GL_QUADS);

			// Bottom Face
			glNormal3f( 0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f,  -0.2f, -2.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  -0.2f,  2.0f);
			glTexCoord2f(0.25f, 1.0f); glVertex3f( 2.0f,  -0.2f,  2.0f);
			glTexCoord2f(0.25f, 0.0f); glVertex3f( 2.0f,  -0.2f, -2.0f);

		glEnd();

	glEndList();


	checker_board_top = checker_board_rest + 1;

	glNewList(checker_board_top,GL_COMPILE);

		glBegin(GL_QUADS);

			// Top Face
			glNormal3f( 0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.6f,  0.11f, -1.6f);
			glTexCoord2f(0.0f, 0.703f); glVertex3f(-1.6f,  0.11f,  1.6f);
			glTexCoord2f(0.703f, 0.703f); glVertex3f( 1.6f,  0.11f,  1.6f);
			glTexCoord2f(0.703f, 0.0f); glVertex3f( 1.6f,  0.11f, -1.6f);

		glEnd();

	glEndList();


	checker_piece_rest = checker_board_top + 1;

	glNewList(checker_piece_rest,GL_COMPILE);

		glBegin(GL_QUAD_STRIP); // Around the edge

			for(int i = 0; i <= 360; i+=40)
			{
				float s = sin(3.141592654*(double)i/180.0), c = cos(3.141592654*(double)i/180.0);
				glNormal3f(s,0.0f,c);

				glTexCoord2f((float)i/360.0f, 1.0f); glVertex3f(-0.13f*c, -0.04f, 0.13f*s);
				glTexCoord2f((float)i/360.0f, 0.0f); glVertex3f(-0.13f*c,  0.04f, 0.13f*s);
			}

		glEnd();

		glBegin(GL_QUAD_STRIP); // Top rim

				glNormal3f(0.0f,1.0f,0.0f);

				for(int i = 0; i <= 360; i+=40)
				{
					float s = sin(3.141592654*(double)i/180.0), c = cos(3.141592654*(double)i/180.0);

					glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f*c,  0.04f, 0.1f*s);
					glTexCoord2f((float)i/360.0f, 0.0f); glVertex3f(-0.13f*c,  0.04f, 0.13f*s);
				}

			glEnd();

			glBegin(GL_QUAD_STRIP); // Inside rim

				for(int i = 0; i <= 360; i+=40)
				{
					float s = sin(3.141592654*(double)i/180.0), c = cos(3.141592654*(double)i/180.0);
					glNormal3f(-s,0.0f,-c);

					glTexCoord2f((float)i/360.0f, 1.0f); glVertex3f(-0.1f*c, 0.02f, 0.1f*s);
					glTexCoord2f((float)i/360.0f, 0.0f); glVertex3f(-0.1f*c, 0.04f, 0.1f*s);
				}

			glEnd();

			glBegin(GL_TRIANGLE_FAN); // Bottom

				glNormal3f(0.0f,-1.0f,0.0f);

				glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, -0.04f, 0.0f); // Center of the fan.

				for(int i = 0; i <= 360; i+=40)
				{
					float s = sin(3.141592654*(double)i/180.0), c = cos(3.141592654*(double)i/180.0);

					glTexCoord2f((float)i/360.0f, 0.0f); glVertex3f(-0.13f*c,  -0.04f, 0.13f*s);
				}

			glEnd();

		glEndList();


		checker_piece_top = checker_piece_rest + 1;

		glNewList(checker_piece_top,GL_COMPILE);

			glBegin(GL_TRIANGLE_FAN); // Top inside

				glNormal3f(0.0f,1.0f,0.0f);

				glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, 0.02f, 0.0f);

				for(int i = 0; i <= 360; i+=40)
				{
					float s = sin(3.141592654*(double)i/180.0), c = cos(3.141592654*(double)i/180.0);

					glTexCoord2f(0.5f*(1-c), 0.5f*(s+1)); glVertex3f(-0.1f*c,  0.02f, 0.1f*s);
				}

			glEnd();

		glEndList();
	}

};
