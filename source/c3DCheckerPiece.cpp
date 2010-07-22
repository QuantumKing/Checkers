
#include "c3DCheckerPiece.h"


c3DCheckerPiece::c3DCheckerPiece (float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
	roll = 0.0f;
	pitch = 0.0f;
	heading = 0.0f;

	boundingbox.left = x - 0.13f;
	boundingbox.right = x + 0.13f;
	boundingbox.front = z + 0.13f;
	boundingbox.back = z - 0.13f;
	boundingbox.top = y + 0.04f ;
	boundingbox.bottom = y - 0.04f;

	color = 0;
	kinged = false;
}


void c3DCheckerPiece::move_to (float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;

	boundingbox.left = x - 0.13f;
	boundingbox.right = x + 0.13f;
	boundingbox.front = z + 0.13f;
	boundingbox.back = z - 0.13f;
	boundingbox.top = y + 0.04f ;
	boundingbox.bottom = y - 0.04f;
}


void c3DCheckerPiece::move_by (float X, float Y, float Z)
{
	x += X;
	y += Y;
	z += Z;

	boundingbox.left = x - 0.13f;
	boundingbox.right = x + 0.13f;
	boundingbox.front = z + 0.13f;
	boundingbox.back = z - 0.13f;
	boundingbox.top = y + 0.04f ;
	boundingbox.bottom = y - 0.04f;
}


float c3DCheckerPiece::X (void) const
{
	return x;
}


float c3DCheckerPiece::Y (void) const
{
	return y;
}


float c3DCheckerPiece::Z (void) const
{
	return z;
}


void c3DCheckerPiece::rotate_to (float roll, float pitch, float heading)
{
	this->roll = roll;
	this->pitch = pitch;
	this->heading = heading;
}


void c3DCheckerPiece::rotate_by (float roll, float pitch, float heading)
{
	this->roll += roll;
	this->pitch += pitch;
	this->heading += heading;

	if(this->roll >= 360.0f)
		this->roll -= 360.0f;
	else if(this->roll <= -360.0f)
		this->roll += 360.0f;

	if(this->pitch >= 360.0f)
		this->pitch -= 360.0f;
	else if(this->pitch <= -360.0f)
		this->pitch += 360.0f;

	if(this->heading >= 360.0f)
		this->heading -= 360.0f;
	else if(this->heading <= -360.0f)
		this->heading += 360.0f;
}


float c3DCheckerPiece::Roll (void) const
{
	return roll;
}


float c3DCheckerPiece::Pitch (void) const
{
	return pitch;
}


float c3DCheckerPiece::Heading (void) const
{
	return heading;
}


const Box3D& c3DCheckerPiece::BoundingBox (void) const
{
	return boundingbox;
}


int c3DCheckerPiece::Color (void) const
{
	return color;
}


bool c3DCheckerPiece::isKinged (void) const
{
	return kinged;
}


void c3DCheckerPiece::setKinged (bool b)
{
	kinged = b;
}


void c3DCheckerPiece::setColor (int color)
{
	this->color = color;
}


bool c3DCheckerPiece::Vector3DIntersect (Vector3D v) const
{
	if( v.x > boundingbox.left && v.x < boundingbox.right )
	{
		if( v.y > boundingbox.bottom && v.y < boundingbox.top )
		{
			if( v.z > boundingbox.back && v.z < boundingbox.front )
			{
				return true;
			}
		}			
	}
	return false;
}


void c3DCheckerPiece::draw (void) const
{
	glPushMatrix();

		glTranslatef(x, y, z);

		glRotatef(roll, 0.0f, 0.0f, 1.0f);
		glRotatef(pitch, 0.0f, 1.0f, 0.0f);
		glRotatef(heading, 1.0f, 0.0f, 0.0f);

		bool red = color == 1 || color == 3;

		GLuint t = red ? glLists::textures[2] : glLists::textures[3];
		glBindTexture(GL_TEXTURE_2D, t);
		glCallList(glLists::checker_piece_rest);

		if( kinged )
		{
			t = red ? glLists::textures[4] : glLists::textures[5];
			glBindTexture(GL_TEXTURE_2D, t);
			glCallList(glLists::checker_piece_top);
		}
		else glCallList(glLists::checker_piece_top);

	glPopMatrix();
}



