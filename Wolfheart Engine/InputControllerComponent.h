#pragma once
#include "EntityComponent.h"
#include "EngineMath.h"
#include "InputMapping.h"
#include "InputEvent.h"

#include <functional>
#include <unordered_map>

class CKeyInputEvent; 

typedef std::function<void(CVector3)> AxisBinding;
typedef std::function<void> ActionBinding;
typedef std::unordered_map<const char*, AxisBinding> AxisMap;

class CInputControllerComponent : public IEntityComponent
{
public:
	CInputControllerComponent();
	~CInputControllerComponent();

	void ProcessInput(CKeyInputEvent* pInputEvent);
	void ProcessKeyInputAxis(ui32 ui32AxisKey);

	void AddMovementInput(CVector3 vecInput);
	CVector3 ConsumeInputVector();

	template<typename FunctionPtr, typename ObjectPtr>
	void CreateAxisBinding(const char* szBindingName, ObjectPtr pObject, FunctionPtr pFunc)
	{
		AxisBinding binding = std::bind(pFunc, pObject, std::placeholders::_1);
		m_axisMap.insert(std::make_pair(szBindingName, binding));
	}

private:
	AxisMap m_axisMap;
	CVector3 m_vecAccumulatedInput;
	CVector3 m_vecLastAccumulatedInput;

	ui32 m_ui32MovementFlags;
};