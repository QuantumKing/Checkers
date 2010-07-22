#ifndef DEFS_H
#define DEFS_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

#include <iostream>
#include <math.h>

class FailedSurface{};

struct Texture			// Holds texture data.
{
	GLuint t;	      // Handle to texture object
	float w;
	float h;
};


Texture Load2DTexture(const char* filename);		// Function to load a texture from a bitmap.

int round(float a);			//Function to round a number.

class Rect		// A 2D bounding box.
{
	public:
		Rect(float l, float r, float t, float b)
		{
			left = l;
			right = r;
			top = t;
			bottom = b;
		};

		Rect (void){};

		float left;
		float right;
		float top;
		float bottom;
};

class Vector3D		// A 3D vector.
{
	public:

		Vector3D(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3D (void) {};

		float x, y, z;
};


class Box3D		// A 3D bounding box.
{
	public:

		Box3D(float left, float right, float front, float back, float top, float bottom)
		{
			this->left = left;
			this->right = right;
			this->front = front;
			this->back = back;
			this->top = top;
			this->bottom = bottom;
		}

		Box3D (void) {};

		float left, right, front, back, top, bottom;
};


namespace glLists		// Definitions for gl lists.
{

	extern GLuint textures[6];
	extern GLuint checker_board_rest;
	extern GLuint checker_board_top;
	extern GLuint checker_piece_rest;
	extern GLuint checker_piece_top;

	void LoadAllTextures (void);
	void BuildLists (void);
};


#endif
