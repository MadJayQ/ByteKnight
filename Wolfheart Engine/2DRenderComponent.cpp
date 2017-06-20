#include "2DRenderComponent.h"

C2DRenderComponent::C2DRenderComponent()
{
}

C2DRenderComponent::C2DRenderComponent(CSprite* sprite)
{
	m_pSprite = sprite;
}

C2DRenderComponent::~C2DRenderComponent()
{
	if (m_pSprite != NULL)
	{
		delete m_pSprite;
		m_pSprite = 0;
	}
}
