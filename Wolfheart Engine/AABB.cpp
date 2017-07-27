#include "AABB.h"

AABB::AABB(CVector3 vecCenter, CVector3 vecHalfSize) :
	m_vecCenter(vecCenter),
	m_vecHalfSize(vecHalfSize)
{

}

AABB::AABB()
{
	m_vecCenter = CVector3::Zero;
	m_vecHalfSize = CVector3::Zero;
}

bool AABB::Contains(const CVector3& p) const
{

	bool bContains = false;
	if (p._x < m_vecCenter._x + m_vecHalfSize._x &&
		p._x > m_vecCenter._x - m_vecHalfSize._x)
	{
		if (p._y < m_vecCenter._y + m_vecHalfSize._y &&
			p._y > m_vecCenter._y + m_vecHalfSize._y)
		{
			bContains = true;
		}
	}

	return bContains;
}

bool AABB::Intersects(const AABB& other) const
{
	bool bIntersects = false;
	if (m_vecCenter._x + m_vecHalfSize._x > other.m_vecCenter._x - other.m_vecHalfSize._x ||
		m_vecCenter._x - m_vecHalfSize._x < other.m_vecCenter._x + other.m_vecHalfSize._x)
	{
		if (m_vecCenter._y + m_vecHalfSize._y > other.m_vecCenter._y - other.m_vecHalfSize._y ||
			m_vecCenter._y - m_vecHalfSize._y < other.m_vecCenter._y + other.m_vecHalfSize._y)
		{
			bIntersects = true;
		}
	}

	return bIntersects;
}
