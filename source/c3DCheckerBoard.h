#include "3Ddefs.h"

class c3DCheckerBoard
{
		float x, y, z;

		float roll, pitch, heading;

		Box3D boundingbox;

	public:

		c3DCheckerBoard (float X, float Y, float Z);

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

};

