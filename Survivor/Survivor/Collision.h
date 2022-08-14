#pragma once
#include "Math.h"

struct Circle {
	Circle(const Vector2& center, float radius);

	Vector2 mCenter;
	float mRadius;
};

bool Intersect(const Circle& a, const Circle& b);
