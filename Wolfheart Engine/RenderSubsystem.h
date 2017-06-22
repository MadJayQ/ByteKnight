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


private:

	void TranslateRenderingRegion(const CVector3 position, SDL_Rect* pRect);
	CVector3 GetEntInterpolatedPosition(CEntityBase* ent);
};