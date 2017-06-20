#include "RenderSubsystem.h"
#include "2DRenderComponent.h"
#include "PositionComponent.h"

#include <SDL.h>
#include <cassert>

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



