#pragma once

#include "EngineMath.h"
#include "ObjectMetadata.h"

class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Tick(float flDeltaTime);

	ENGINE_CLASS(CGameWorld);
};
