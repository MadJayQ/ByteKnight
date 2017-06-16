#pragma once
#include "EngineMath.h"
#include "ObjectMetadata.h"

class CGlobalVars
{
public:
	ENGINE_CLASS(CGlobalVars);
	CGlobalVars();
	~CGlobalVars();

	ui32 ui32TickCount = 0;
	ui64 ui64FrameCount = 0;
	ui32 ui32Tickrate = 0;

	float flInterpolation = 0.f;
	float flFrameTime = 0.f;
	float flTickInterval = 0.f;
	float flCurrentTime = 0.f;
};



CGlobalVars* GetGlobalVars();