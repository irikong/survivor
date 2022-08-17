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

float AABB::MinDistSq(const Vector2& point) const
{
	float dx = Math::Max(mMin.x - point.x, 0.0f);
	dx = Math::Max(dx, point.x - mMax.x);
	float dy = Math::Max(mMin.y - point.y, 0.0f);
	dy = Math::Max(dy, point.y - mMax.y);

	return dx * dx + dy * dy;
}

bool Intersect(const Circle& a, const Circle& b)
{
	float distSq = (a.mCenter - b.mCenter).LengthSq();
	float radiusSum = a.mRadius + b.mRadius;

	return distSq <= (radiusSum * radiusSum);
}

bool Intersect(const AABB& a, const AABB& b)
{
	bool isOK = (a.mMax.x < b.mMin.x) || (a.mMax.y < b.mMin.y) || (b.mMax.x < a.mMin.x) || (b.mMax.y < a.mMin.y);

	return !isOK;
}

bool Intersect(const Circle& circle, const AABB& aabb)
{
	float minDistSq = aabb.MinDistSq(circle.mCenter);

	return minDistSq <= circle.mRadius * circle.mRadius;
}

bool Intersect(const AABB& aabb, const Circle& circle)
{
	return Intersect(circle, aabb);
}
