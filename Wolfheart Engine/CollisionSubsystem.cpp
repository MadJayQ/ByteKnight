#include "CollisionSubsystem.h"

CCollisionSubsystem::CCollisionSubsystem()
{
}

CCollisionSubsystem::~CCollisionSubsystem()
{
}

void CCollisionSubsystem::ApplyMovement(CEntityBase* ent, float flDeltaTime)
{

}

void CCollisionSubsystem::Tick(float flDeltaTime)
{

}

void CCollisionSubsystem::RegisterEntity(CEntityBase* ent)
{
	IGameSubsystem::RegisterEntity(ent);
}

void CCollisionSubsystem::UnRegisterEntity(CEntityBase* ent)
{
	IGameSubsystem::UnRegisterEntity(ent);
}
