#pragma once

#include "Vector3.h"

class AABB
{
public:
	AABB(CVector3 vecCenter, CVector3 vecHalfSize);
	AABB();

	bool Contains(const CVector3& p) const ;
	bool Intersects(const AABB& other) const;

	CVector3 m_vecCenter;
	CVector3 m_vecHalfSize;
};