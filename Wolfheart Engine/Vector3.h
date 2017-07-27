#pragma once

#include <math.h>

class CVector3
{
public:
	explicit CVector3(float x, float y, float z);
	CVector3();

	void operator=(const CVector3& other);
	CVector3 operator+(const CVector3& other);
	CVector3 operator-(const CVector3& other);
	CVector3 operator*(const CVector3& other);
	CVector3 operator/(const CVector3& other);

	CVector3 operator*(const float& other);
	CVector3 operator/(const float& other);

	void operator+=(const CVector3& other);
	void operator-=(const CVector3& other);
	void operator*=(const CVector3& other);
	void operator/=(const CVector3& other);

	float operator[](int idx);

	CVector3 LerpTo(const CVector3& other, float t);

	bool IsZero();

	static CVector3 Zero;

	float _x, _y, _z;
};