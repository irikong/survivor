#pragma once
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

private:
	float mat[4][4];
};