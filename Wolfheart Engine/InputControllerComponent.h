#pragma once
#include "EntityComponent.h"
#include "EngineMath.h"

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

	template<typename FunctionPtr, typename ObjectPtr>
	void CreateAxisBinding(const char* szBindingName, ObjectPtr pObject, FunctionPtr pFunc)
	{
		AxisBinding binding = std::bind(pFunc, pObject, std::placeholders::_1);
		m_axisMap.insert(std::make_pair(szBindingName, binding));
	}

private:
	AxisMap m_axisMap;
};