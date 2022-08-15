#include "Collision.h"

Circle::Circle() :
	mCenter(Vector2::Zero),
	mRadius(0.0f)
{
}

Circle::Circle(const Vector2& center, float radius) :
	mCenter(center),
	mRadius(radius)
{
}

AABB::AABB() : 
	mMin(Vector2::Zero),
	mMax(Vector2::Zero)
{
}

AABB::AABB(const Vector2& min, const Vector2& max) :
	mMin(min),
	mMax(max)
{
}

bool Intersect(const Circle& a, const Circle& b)
{
	float distSq = (a.mCenter - b.mCenter).LengthSq();
	float radiusSum = a.mRadius + b.mRadius;

	return distSq <= (radiusSum * radiusSum);
}
