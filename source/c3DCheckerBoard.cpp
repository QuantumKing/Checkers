#include "c3DCheckerBoard.h"


c3DCheckerBoard::c3DCheckerBoard (float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
	roll = 0.0f;
	pitch = 0.0f;
	heading = 0.0f;
}


void c3DCheckerBoard::move_to (float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}


void c3DCheckerBoard::move_by (float X, float Y, float Z)
{
	x += X;
	y += Y;
	z += Z;
}


float c3DCheckerBoard::X (void) const
{
	return x;
}


float c3DCheckerBoard::Y (void) const
{
	return y;
}


float c3DCheckerBoard::Z (void) const
{
	return z;
}


void c3DCheckerBoard::rotate_to (float roll, float pitch, float heading)
{
	this->roll = roll;
	this->pitch = pitch;
	this->heading = heading;
}


void c3DCheckerBoard::rotate_by (float roll, float pitch, float heading)
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


float c3DCheckerBoard::Roll (void) const
{
	return roll;
}


float c3DCheckerBoard::Pitch (void) const
{
	return pitch;
}


float c3DCheckerBoard::Heading (void) const
{
	return heading;
}


const Box3D& c3DCheckerBoard::BoundingBox (void) const
{
	return boundingbox;
}


bool c3DCheckerBoard::Vector3DIntersect (Vector3D v) const
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


void c3DCheckerBoard::draw (void) const
{
	glPushMatrix();

		glTranslatef(x, y, z);

		glRotatef(roll, 0.0f, 0.0f, 1.0f);
		glRotatef(pitch, 0.0f, 1.0f, 0.0f);
		glRotatef(heading, 1.0f, 0.0f, 0.0f);

		glBindTexture(GL_TEXTURE_2D, glLists::textures[0]);
		glCallList(glLists::checker_board_rest);

		glBindTexture(GL_TEXTURE_2D, glLists::textures[1]);
		glCallList(glLists::checker_board_top);

	glPopMatrix();
}


