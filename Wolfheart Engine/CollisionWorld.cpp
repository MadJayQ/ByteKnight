#include "CollisionWorld.h"

#include "PositionComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"

CCollisionWorld::CCollisionWorld()
{

}

CCollisionWorld::~CCollisionWorld()
{

}

void CCollisionWorld::ApplyMovementWithCollision(
	CEntityBase* ent,
	float flDeltaTime
)
{
	CPositionComponent* pPositionComponent = ent->GetComponent<CPositionComponent>();
	CMovementComponent* pMovementComponent = ent->GetComponent<CMovementComponent>();
	CCollisionComponent* pCollisionComponent = ent->GetComponent<CCollisionComponent>();

	CVector3 vecPosition = pPositionComponent->GetPositon();
	CVector3 vecVelocity = pMovementComponent->GetVelocity();
	CVector3 vecPredictedPosition = vecPosition;
	if (pMovementComponent->Accelerates())
	{
		vecVelocity += pMovementComponent->GetAcceleration();
	}
	vecPredictedPosition += (vecVelocity * flDeltaTime);
	AdjustPositionToMapBounds(vecPredictedPosition, pCollisionComponent->GetCollisionRect());
	pPositionComponent->SetPosition(vecPredictedPosition);
}

void CCollisionWorld::OnEventNotify(CEntityBase* ent, IEvent* e)
{

}

void CCollisionWorld::AdjustPositionToMapBounds(CVector3& vec, CRectangle boundingRect)
{
	float left = vec._x;
	float right = vec._x + boundingRect.x;
	float top = vec._y;
	float bottom = vec._y + boundingRect.h;

	if (left < m_boundingRectangle.x)
	{
		vec._x = m_boundingRectangle.x;
	}
	else if (right > m_boundingRectangle.x + m_boundingRectangle.w)
	{
		vec._x = (m_boundingRectangle.x + m_boundingRectangle.w) - boundingRect.w;
	}
	if (top < m_boundingRectangle.y)
	{
		vec._y = m_boundingRectangle.y;
	}
	else if (bottom > m_boundingRectangle.y + m_boundingRectangle.h)
	{
		vec._y = (m_boundingRectangle.y + m_boundingRectangle.h) - boundingRect.h;
	}

}
