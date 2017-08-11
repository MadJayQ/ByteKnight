#include "UnitMetrics.h"

void CUnitMetrics::SetPixelsPerMeter(float pixels)
{
	m_flPixelsPerMeter = pixels;
}

void CUnitMetrics::SetPixelsPerMeter(float pixels, float meter)
{
	m_flPixelsPerMeter = pixels / meter;
}
