#include "RenderSubsystem.h"
#include "2DRenderComponent.h"
#include "PositionComponent.h"
#include "GlobalVars.h"

#include <SDL.h>
#include <cassert>
#include <iostream>

CRenderSubsystem::CRenderSubsystem()
{

}

CRenderSubsystem::~CRenderSubsystem()
{

}

void CRenderSubsystem::Tick(float flDeltaTime)
{

}

void CRenderSubsystem::Render(CGraphicsDevice* pGraphicsDevice)
{
	for (auto& ent : m_registeredEntities)
	{
		if (ent->HasComponent<C2DRenderComponent>() && ent->HasComponent<CPositionComponent>())
		{
			C2DRenderComponent* pRenderComponent = ent->GetComponent<C2DRenderComponent>();
			CPositionComponent* pPositionComponent = ent->GetComponent<CPositionComponent>();
			if (!pRenderComponent || !pPositionComponent)
				continue;

			auto pHardwareRenderer = pGraphicsDevice->GetHardwareRenderer();
			auto pSprite = pRenderComponent->GetSprite();
			SDL_Rect renderingRegion = pRenderComponent->GetSprite()->GetRenderingRect();
			TranslateRenderingRegion(
				GetEntInterpolatedPosition(ent),
				&renderingRegion
			);
			if (pSprite->GetTexture() == NULL) continue;
			SDL_RenderCopy(
				pHardwareRenderer,
				pSprite->GetTexture(),
				NULL,
				&renderingRegion
			);
		}
	}
}

//This function converts our floating point coordinates into pixel locations
void CRenderSubsystem::TranslateRenderingRegion(const CVector3 position, SDL_Rect* pRect)
{
	ui32 ui32ConvertedX = (ui32)(std::lroundf(position._x));
	ui32 ui32ConvertedY = (ui32)(std::lroundf(position._y));

	pRect->x = ui32ConvertedX;
	pRect->y = ui32ConvertedY;
}

CVector3 CRenderSubsystem::GetEntInterpolatedPosition(CEntityBase* ent)
{
	float flInterpolation = GetGlobalVars()->flInterpolation;
	CPositionComponent* pPositionComponent = ent->GetComponent<CPositionComponent>();

	v3 vecCurrentPos = pPositionComponent->GetPositon();
	v3 vecLastPos = pPositionComponent->GetOldPosition();
	v3 vecInterpolatedPos = Math::Lerp(vecLastPos, vecCurrentPos, flInterpolation);	
	return (ent->ShouldInterpolate()) ? vecInterpolatedPos : vecCurrentPos;
}



