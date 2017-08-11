#include "Timer.h"
#include "Defines.h"

#include <chrono>


GLOBAL std::chrono::duration<i64, std::nano> s_lastDelta;
GLOBAL tickperiod_t m_startPeriod;

CTimer::CTimer()
{
	m_startPeriod = std::chrono::steady_clock::now();
	s_lastDelta = m_startPeriod - m_startPeriod;
	m_bTicking = false;
}

CTimer::~CTimer()
{
	
}

ui64 CTimer::GetCurrentTimeStamp() const
{
	if (m_bTicking)
	{
		s_lastDelta = std::chrono::steady_clock::now() - m_startPeriod;
	}
	else
	{
		m_startPeriod = std::chrono::steady_clock::now() - s_lastDelta;
	}
	return std::chrono::duration_cast<std::chrono::microseconds>(
		s_lastDelta
	).count();
}
