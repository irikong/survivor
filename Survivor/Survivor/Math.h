#pragma once
#include <cmath>

namespace Math {
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
}

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

	static Matrix3 CreateScale(float xScale, float yScale);
	static Matrix3 CreateRotation(float theta);
	static Matrix3 CreateTranslation(float xTrans, float yTrans);

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

	static Matrix4 CreateScale(float xScale, float yScale, float zScale);
	static Matrix4 CreateRotationX(float theta);
	static Matrix4 CreateRotationY(float theta);
	static Matrix4 CreateRotationZ(float theta);
	static Matrix4 CreateTranslation(float xTrans, float yTrans, float zTrans);

private:
	float mat[4][4];
};