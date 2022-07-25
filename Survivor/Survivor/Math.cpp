#include "Math.h"

// Matrix3
Matrix3::Matrix3():
	mat{ { 0 } }
{

}

Matrix3::Matrix3(float _mat[3][3])
{
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			mat[r][c] = _mat[r][c];
		}
	}
}

Matrix3::Matrix3(const Matrix3& rhs)
{
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			mat[r][c] = rhs.mat[r][c];
		}
	}
}

Matrix3& Matrix3::operator=(const Matrix3& rhs)
{
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			mat[r][c] = rhs.mat[r][c];
		}
	}

	return *this;
}

Matrix3::~Matrix3()
{
}

Matrix3 operator*(const Matrix3& lhs, const Matrix3& rhs)
{
	Matrix3 ret;

	// 캐시 효율을 위해 rkc 순으로 연산
	for (int r = 0; r < 3; r++) {
		for (int k = 0; k < 3; k++) {
			float temp = lhs.mat[r][k];

			for (int c = 0; c < 3; c++) {
				ret.mat[r][c] += temp * rhs.mat[k][c];
			}
		}
	}

	return ret;
}

Matrix3& Matrix3::operator*=(const Matrix3& rhs)
{
	*this = *this * rhs;

	return *this;
}

Matrix3 Matrix3::CreateScale(float xScale, float yScale)
{
	float temp[3][3] = {
		{ xScale, 0.0f, 0.0f },
		{ 0.0f, yScale, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
	};

	return Matrix3(temp);
}

Matrix3 Matrix3::CreateRotation(float theta)
{
	float temp[3][3] = {
		{ Math::Cos(theta), Math::Sin(theta), 0.0f },
		{ -Math::Sin(theta), Math::Cos(theta), 0.0f },
		{ 0.0f, 0.0f, 1.0f },
	};

	return Matrix3(temp);
}

// Matrix4
Matrix4::Matrix4():
	mat{ {0} }
{

}

Matrix4::Matrix4(float _mat[4][4])
{
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			mat[r][c] = _mat[r][c];
		}
	}
}

Matrix4::Matrix4(const Matrix4& rhs)
{
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			mat[r][c] = rhs.mat[r][c];
		}
	}
}

Matrix4& Matrix4::operator=(const Matrix4& rhs)
{
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			mat[r][c] = rhs.mat[r][c];
		}
	}

	return *this;
}

Matrix4::~Matrix4()
{
}

Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
{
	// TODO: Strassen 행렬곱
	Matrix4 ret;
	
	// 캐시 효율을 위해 rkc 순으로 연산
	for (int r = 0; r < 4; r++) {
		for (int k = 0; k < 4; k++) {
			float temp = lhs.mat[r][k];

			for (int c = 0; c < 4; c++) {
				ret.mat[r][c] += temp * rhs.mat[k][c];
			}
		}
	}

	return ret;
}

Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
	*this = *this * rhs;

	return *this;
}

Matrix4 Matrix4::CreateScale(float xScale, float yScale, float zScale)
{
	float temp[4][4] = {
		{ xScale, 0.0f, 0.0f, 0.0f },
		{ 0.0f, yScale, 0.0f, 0.0f },
		{ 0.0f, 0.0f, zScale, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};

	return Matrix4(temp);
}

Matrix4 Matrix4::CreateRotationX(float theta)
{
	float temp[4][4] = {
		{ 1.0f, 0.0f, 0.0f , 0.0f },
		{ 0.0f, Math::Cos(theta), Math::Sin(theta), 0.0f },
		{ 0.0f, -Math::Sin(theta), Math::Cos(theta), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	};

	return Matrix4(temp);
}

Matrix4 Matrix4::CreateRotationY(float theta)
{
	float temp[4][4] = {
		{ Math::Cos(theta), 0.0f, -Math::Sin(theta), 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ Math::Sin(theta), 0.0f, Math::Cos(theta), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	};

	return Matrix4(temp);
}

Matrix4 Matrix4::CreateRotationZ(float theta)
{
	float temp[4][4] = {
		{ Math::Cos(theta), Math::Sin(theta), 0.0f, 0.0f },
		{ -Math::Sin(theta), Math::Cos(theta), 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	};

	return Matrix4(temp);
}
