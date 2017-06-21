#pragma once

#include <vector>
#include <memory>

#include "GameSubsystem.h"

class CMovementSubsystem : public IGameSubsystem
{
public:
	CMovementSubsystem();
	~CMovementSubsystem();

	virtual void Tick(float flDeltaTime) override;
};