#pragma once

#include "EntityComponent.h"
#include "Vector3.h"

class CPositionComponent : public IEntityComponent
{
public:
	CPositionComponent();
	~CPositionComponent();

	CVector3& GetPositon()
	{
		return m_vecPosition;
	}

	CVector3& GetOldPosition()
	{
		return m_vecOldPosition;
	}

	void SetPosition(CVector3 pos) { m_vecPosition = pos; }
	void SetOldPosition(CVector3 pos) { m_vecOldPosition = pos; }

private:
	CVector3 m_vecPosition;
	CVector3 m_vecOldPosition;
};
