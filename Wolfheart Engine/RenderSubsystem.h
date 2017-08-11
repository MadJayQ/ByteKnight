#pragma once

#include "GameSubsystem.h"
#include "GraphicDevice.h"
#include <Box2D\Box2D.h>

class CRenderSubsystem : public IGameSubsystem, public b2Draw
{
public:
	CRenderSubsystem();
	~CRenderSubsystem();

	virtual void Tick(float flDeltaTime) override;
	void Render();

	/// Draw a closed polygon provided in CCW order.
	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	/// Draw a solid closed polygon provided in CCW order.
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	/// Draw a circle.
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
	/// Draw a solid circle.
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
	/// Draw a line segment.
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	virtual void DrawTransform(const b2Transform& xf) override;
	/// Draw a point.
	virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;

	void RegisterGraphicsDevice(CGraphicsDevice* device) { m_pGraphicsDevice = device; }

private:
	void TranslateRenderingRegion(const CVector3 position, SDL_Rect* pRect);
	CVector3 GetEntInterpolatedPosition(CEntityBase* ent);

private:
	CGraphicsDevice* m_pGraphicsDevice;
};