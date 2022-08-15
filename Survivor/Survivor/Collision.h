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
	
	Vector2 mMin; // LD
	Vector2 mMax; // RU
};

bool Intersect(const Circle& a, const Circle& b);
