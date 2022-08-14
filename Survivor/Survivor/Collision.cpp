#include "Collision.h"

Circle::Circle(const Vector2& center, float radius) : 
	mCenter(center),
	mRadius(radius)
{

}

bool Intersect(const Circle& a, const Circle& b)
{
	float distSq = (a.mCenter - b.mCenter).LengthSq();
	float radiusSum = a.mRadius + b.mRadius;

	return distSq <= (radiusSum * radiusSum);
}
