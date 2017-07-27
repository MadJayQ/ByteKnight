#include "Vector3.h"

#include <cassert>

CVector3 CVector3::Zero = CVector3(0.f, 0.f, 0.f);

CVector3::CVector3(float x, float y, float z) :
	_x(x),
	_y(y),
	_z(z)
{

}

CVector3::CVector3()
{
	_x = 0.f; _y = 0.f; _z = 0.f;
}

void CVector3::operator=(const CVector3 & other)
{
	this->_x = other._x;
	this->_y = other._y;
	this->_z = other._z;
}

CVector3 CVector3::operator+(const CVector3& other)
{
	return CVector3(
		this->_x + other._x,
		this->_y + other._y,
		this->_z + other._z
	);
}

CVector3 CVector3::operator-(const CVector3& other)
{
	return CVector3(
		this->_x - other._x,
		this->_y - other._y,
		this->_z - other._z
	);
}

CVector3 CVector3::operator*(const CVector3& other)
{
	return CVector3(
		this->_x * other._x,
		this->_y * other._y,
		this->_z * other._z
	);
}

CVector3 CVector3::operator/(const CVector3& other)
{
	return CVector3(
		this->_x / other._x,
		this->_y / other._y,
		this->_z / other._z
	);
}

CVector3 CVector3::operator*(const float & other)
{
	return CVector3(
		this->_x * other,
		this->_y * other,
		this->_z * other
	);
}

CVector3 CVector3::operator/(const float & other)
{
	return CVector3(
		this->_x / other,
		this->_y / other,
		this->_z / other
	);
}

void CVector3::operator+=(const CVector3& other)
{
	this->_x += other._x;
	this->_y += other._y;
	this->_z += other._z;
}

void CVector3::operator-=(const CVector3& other)
{
	this->_x -= other._x;
	this->_y -= other._y;
	this->_z -= other._z;
}

void CVector3::operator*=(const CVector3& other)
{
	this->_x *= other._x;
	this->_y *= other._y;
	this->_z *= other._z;
}

void CVector3::operator/=(const CVector3& other)
{
	this->_x /= other._x;
	this->_y /= other._y;
	this->_z /= other._z;
}

bool CVector3::IsZero()
{
	return (
		this->_x != 0 &&
		this->_y != 0 &&
		this->_z != 0
	);
}

float CVector3::operator[](int idx)
{
	assert(idx <= 2 && idx >= 0);
	switch (idx)
	{
	case 0: return _x;
	case 1: return _y;
	case 2: return _z;
	}
}

CVector3 CVector3::LerpTo(const CVector3& other, float t)
{
	float flTimeFraction = (t - 1.f);
	return CVector3(
		flTimeFraction * this->_x + t * other._x,
		flTimeFraction * this->_y + t * other._y,
		flTimeFraction * this->_z + t * other._z
	);
}