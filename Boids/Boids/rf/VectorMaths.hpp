#include <cmath>

namespace rf
{
	namespace VectorMaths
	{
		struct Vector
		{
			Vector()
			{
			}

			Vector(float X, float Y)
			{
				x = X;
				y = Y;
			}

			float x = 0;
			float y = 0;
		};

		static float getMagnitude(const Vector& v)
		{
			return std::sqrt(v.x*v.x + v.y*v.y);
		}

		static Vector normalize(const Vector& v)
		{
			return Vector(v.x / getMagnitude(v), v.y / getMagnitude(v));
		}
	}
}