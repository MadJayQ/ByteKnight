#include "PositionComponent.h"

CPositionComponent::CPositionComponent()
{
	m_vecPosition = CVector3(0.f, 0.f, 0.f);
	m_vecOldPosition = CVector3(0.f, 0.f, 0.f);
}

CPositionComponent::~CPositionComponent()
{
}
