#include "Entity.h"

CEntityBase::CEntityBase(ui32 ui32EntityID, CGameWorld* pGameWorld) :
	m_ui32EntityID(ui32EntityID),
	m_pGameWorld(pGameWorld)
{

}

CEntityBase::~CEntityBase()
{

}
