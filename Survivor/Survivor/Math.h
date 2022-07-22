#pragma once
class Matrix3
{
public:
	Matrix3();
	Matrix3(float _mat[3][3]);
	Matrix3(const Matrix3& rhs);
	Matrix3& operator=(const Matrix3& rhs);
	~Matrix3();

	friend Matrix3 operator*(const Matrix3& left, const Matrix3& right);
	Matrix3& operator*=(const Matrix3& right);

private:
	float mat[3][3];
};

