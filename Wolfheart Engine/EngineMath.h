#pragma once

#include "Vector3.h"
#include "Rectangle.h"

#include <algorithm>

typedef unsigned long long ui64;
typedef signed long long i64;
typedef unsigned int ui32;
typedef signed int i32;
typedef unsigned short ui16;
typedef signed short u16;
typedef unsigned char ui8;
typedef signed char i8;


typedef CVector3 v3;
typedef CRectangle Rect;

namespace Math
{
	float Lerp(float f0, float f1, float t);
	v3 Lerp(v3 v0, v3 v1, float t);
	template<class T>
	const T& clamp(const T& x, const T& upper, const T& lower) {
		return std::min(upper, std::max(x, lower));
	}
}

