#pragma once

#include "EntityComponent.h"
#include "Sprite.h"


#include <memory>
class C2DRenderComponent : public IEntityComponent
{
public:
	C2DRenderComponent();
	C2DRenderComponent(CSprite* sprite);
	~C2DRenderComponent();

	void SetSprite(CSprite* sprite) { m_pSprite = std::make_unique<CSprite>(sprite); }
	CSprite* GetSprite() const { return m_pSprite.get(); }


private:
	std::unique_ptr<CSprite> m_pSprite; //Replace later w/ texture atlas for animated sprite components
};
