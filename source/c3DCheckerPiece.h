#include "3Ddefs.h"

class c3DCheckerPiece
{
		float x, y, z;

		float roll, pitch, heading;

		Box3D boundingbox;

		int color; // 1 or 3 == red. 2 or 4 == black.

		bool kinged;

	public:

		c3DCheckerPiece (float X, float Y, float Z);

		void draw (void) const;

		void move_to (float X, float Y, float Z);

		void move_by (float X, float Y, float Z);

		float X (void) const;

		float Y (void) const;

		float Z (void) const;

		void rotate_to (float roll, float pitch, float heading);

		void rotate_by (float roll, float pitch, float heading);

		float Roll (void) const;

		float Pitch (void) const;

		float Heading (void) const;

		const Box3D& BoundingBox (void) const;

		bool Vector3DIntersect (Vector3D v) const;

		int Color (void) const;

		void setColor (int color);

		bool isKinged (void) const;

		void setKinged (bool);
};

