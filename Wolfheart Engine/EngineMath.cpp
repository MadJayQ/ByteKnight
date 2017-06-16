#include "EngineMath.h"

float Math::Lerp(float f0, float f1, float t)
{
	return (1.f - t) * f0 + t * f1;
}

v3 Math::Lerp(v3 v0, v3 v1, float t)
{
	return v0.LerpTo(v1, t);
}