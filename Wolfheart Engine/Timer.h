#pragma once

#include "EngineMath.h"
#include "ObjectMetadata.h"
#include <chrono>
#include <ratio>

typedef std::chrono::time_point<std::chrono::steady_clock> tickperiod_t;

typedef std::ratio<1i64, 1i64> Seconds;
typedef std::micro Microseconds;
typedef std::milli Milliseconds;
typedef std::nano Nanoseconds;

typedef void(__thiscall* TickFunction_t)(float);
class CTimer
{
	ENGINE_CLASS(CTimer);
public:
	explicit CTimer();
	~CTimer();

	ui64 GetCurrentTimeStamp() const;
	
	template<typename UpdateFn>
	void Tick(const UpdateFn& update)
	{
		if (!m_bTicking) return;

		ui64 ui64CurrentTime = GetCurrentTimeStamp();
		ui64 ui64TimeDelta = ui64CurrentTime - m_ui64LastTime;

		if (ui64TimeDelta > MAX_DELTA)
		{
			ui64TimeDelta = MAX_DELTA;
		}

		ui64TimeDelta *= TICKS_PER_SECOND;
		ui64TimeDelta /= 1e6;
	}

	void StartTimer() { m_bTicking = true; }
	void StopTimer() { m_bTicking = false; }

	template<typename GivenTime, typename ConvertedTime>
	double long TimeConversion(double long inputTime)
	{
		/*
		auto duration = std::chrono::duration_cast<ConvertedTime>(
			std::chrono::duration<double long, GivenTime>(inputTime)
		);
		*/
		typedef std::chrono::duration<double long, ConvertedTime> Chrono_ConvertedTime;
		typedef std::chrono::duration<double long, GivenTime> Chrono_GivenTime;

		Chrono_ConvertedTime convertedDuration = std::chrono::duration_cast<Chrono_ConvertedTime>(
			Chrono_GivenTime(inputTime)
		);

		return convertedDuration.count();

	}
private:
	bool m_bTicking;

	tickperiod_t m_startPeriod;

	ui64 m_ui64LastTime = 0;
	ui32 m_ui32FrameCount = 0;
	ui32 m_ui32FramesPerSecond = 0;
};