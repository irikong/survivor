#pragma once
#include <cmath>

namespace Math {
	const float PI = 3.1415926535f;

	inline float Abs(float value)
	{
		return fabs(value);
	}

	inline float Cos(float theta)
	{
		return cosf(theta);
	}

	inline float Sin(float theta)
	{
		return sinf(theta);
	}

	inline float Tan(float theta)
	{
		return tanf(theta);
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		return (fabs(val) <= epsilon);
	}
}

class Vector2
{
public:
	float x;
	float y;

	Vector2();
	explicit Vector2(float px, float py);

	void Set(float px, float py);

	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator*(const Vector2& vec, float scalar);
	friend Vector2 operator*(float scalar, const Vector2& vec);

	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator*=(float scalar);

	bool operator==(const Vector2& rhs);
	bool operator!=(const Vector2& rhs);

	float LengthSq();
	float Length();
	void Normalize();
	static Vector2 Normalize(const Vector2& vec);
	static float Dot(const Vector2& lhs, const Vector2& rhs);

	static const Vector2 Zero;
};

class Matrix3
{
public:
	Matrix3();
	Matrix3(float _mat[3][3]);
	Matrix3(const Matrix3& rhs);
	Matrix3& operator=(const Matrix3& rhs);
	~Matrix3();

	friend Matrix3 operator*(const Matrix3& lhs, const Matrix3& rhs);
	Matrix3& operator*=(const Matrix3& rhs);

	static Matrix3 CreateScale(float scale);
	static Matrix3 CreateScale(float xScale, float yScale);
	static Matrix3 CreateRotation(float theta);
	static Matrix3 CreateTranslation(float xTrans, float yTrans);
	static Matrix3 CreateViewProj(float width, float height);

	const float* GetAsFloatPtr() const;

private:
	float mat[3][3];
};

class Matrix4
{
public:
	Matrix4();
	Matrix4(float _mat[4][4]);
	Matrix4(const Matrix4& rhs);
	Matrix4& operator=(const Matrix4& rhs);
	~Matrix4();

	friend Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs);
	Matrix4& operator*=(const Matrix4& rhs);

	static Matrix4 CreateScale(float scale);
	static Matrix4 CreateScale(float xScale, float yScale, float zScale);
	static Matrix4 CreateRotationX(float theta);
	static Matrix4 CreateRotationY(float theta);
	static Matrix4 CreateRotationZ(float theta);
	static Matrix4 CreateTranslation(float xTrans, float yTrans, float zTrans);
	static Matrix4 CreateViewProj(float width, float height);

	const float* GetAsFloatPtr() const;

private:
	float mat[4][4];
};