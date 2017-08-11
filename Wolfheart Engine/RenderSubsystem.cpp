#include "RenderSubsystem.h"
#include "2DRenderComponent.h"
#include "PositionComponent.h"
#include "GlobalVars.h"
#include "UnitMetrics.h"

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <cassert>
#include <iostream>

CRenderSubsystem::CRenderSubsystem()
{

}

CRenderSubsystem::~CRenderSubsystem()
{

}

Uint32 b2ColorToUint32(const b2Color& color)
{
	uint8 r = (uint8)(color.r * 255);
	uint8 g = (uint8)(color.g * 255);
	uint8 b = (uint8)(color.b * 255);
	uint8 a = (uint8)(color.a * 255);

	Uint32 ret = r << 24 | g << 16 | b << 8 | a;
	return ret;
}

void CRenderSubsystem::Tick(float flDeltaTime)
{

}

void CRenderSubsystem::Render()
{
	for (auto& ent : m_registeredEntities)
	{
		if (ent->HasComponent<C2DRenderComponent>() && ent->HasComponent<CPositionComponent>())
		{
			C2DRenderComponent* pRenderComponent = ent->GetComponent<C2DRenderComponent>();
			CPositionComponent* pPositionComponent = ent->GetComponent<CPositionComponent>();
			if (!pRenderComponent || !pPositionComponent)
				continue;

			auto pHardwareRenderer = m_pGraphicsDevice->GetHardwareRenderer();
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

void CRenderSubsystem::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	Sint16 vx[8];
	Sint16 vy[8];
	for (int i = 0; i < vertexCount; i++)
	{
		vx[i] = vertices[i].x;
		vy[i] = vertices[i].y;
	}

	polygonColor(
		m_pGraphicsDevice->GetHardwareRenderer(),
		vx,
		vy,
		vertexCount,
		b2ColorToUint32(color)
	);
}

void CRenderSubsystem::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	Sint16 vx[8];
	Sint16 vy[8];
	for (int i = 0; i < vertexCount; i++)
	{
		vx[i] = CUnitMetrics::Instance()->ConvertToPixels<Meters>(vertices[i].x);
		vy[i] = CUnitMetrics::Instance()->ConvertToPixels<Meters>(vertices[i].y);
	}

	filledPolygonColor(
		m_pGraphicsDevice->GetHardwareRenderer(),
		vx,
		vy,
		vertexCount,
		b2ColorToUint32(color)
	);
}

void CRenderSubsystem::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	circleColor(
		m_pGraphicsDevice->GetHardwareRenderer(),
		center.x,
		center.y,
		radius,
		b2ColorToUint32(color)
	);
}

void CRenderSubsystem::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	filledCircleColor(
		m_pGraphicsDevice->GetHardwareRenderer(),
		center.x,
		center.y,
		radius,
		b2ColorToUint32(color)
	);
}

void CRenderSubsystem::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	lineColor(
		m_pGraphicsDevice->GetHardwareRenderer(),
		p1.x,
		p1.y,
		p2.x,
		p2.y,
		b2ColorToUint32(color)
	);
}

void CRenderSubsystem::DrawTransform(const b2Transform& xf)
{

}

void CRenderSubsystem::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{

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



