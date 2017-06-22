#include "EngineMath.h"

float Math::Lerp(float f0, float f1, float t)
{
	return (1.f - t) * f0 + t * f1;
}

v3 Math::Lerp(v3 v0, v3 v1, float t)
{
	return v3(
		Lerp(v0._x, v1._x, t),
		Lerp(v0._y, v1._y, t),
		Lerp(v0._z, v1._z, t)
	);
}