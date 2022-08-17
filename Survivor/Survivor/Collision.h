#pragma once
#include "Math.h"

struct Circle {
	Circle();
	Circle(const Vector2& center, float radius);

	Vector2 mCenter;
	float mRadius;
};

struct AABB { // Axis-ALigned Bounding Box
	AABB();
	AABB(const Vector2& min, const Vector2& max);

	float MinDistSq(const Vector2& point) const;
	
	Vector2 mMin; // LD
	Vector2 mMax; // RU
};

bool Intersect(const Circle& a, const Circle& b);
bool Intersect(const AABB& a, const AABB& b);

bool Intersect(const Circle& circle, const AABB& aabb);
bool Intersect(const AABB& aabb, const Circle& circle);