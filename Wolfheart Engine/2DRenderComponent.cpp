#include "2DRenderComponent.h"

C2DRenderComponent::C2DRenderComponent()
{
}

C2DRenderComponent::C2DRenderComponent(CSprite* sprite)
{
	m_pSprite = std::make_unique<CSprite>(sprite);
}

C2DRenderComponent::~C2DRenderComponent()
{
	if (m_pSprite.get() != NULL)
	{
		m_pSprite.reset();
		m_pSprite.release();
	}
}
