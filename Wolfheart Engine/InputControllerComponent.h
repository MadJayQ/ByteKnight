#pragma once
#include "EntityComponent.h"
class CKeyInputEvent; 

class CInputControllerComponent : public IEntityComponent
{
public:
	CInputControllerComponent();
	~CInputControllerComponent();

	void ProcessInput(CKeyInputEvent* pInputEvent);
};