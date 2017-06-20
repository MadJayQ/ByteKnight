#pragma once

#include "GameSubsystem.h"
#include "GraphicDevice.h"

class CRenderSubsystem : public IGameSubsystem
{
public:
	CRenderSubsystem();
	~CRenderSubsystem();

	virtual void Tick(float flDeltaTime) override;
	void Render(CGraphicsDevice* pGraphicsDevice);
};