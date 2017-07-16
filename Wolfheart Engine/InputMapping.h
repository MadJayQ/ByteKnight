#pragma once

#include <memory>
#include <unordered_map>

#include "EngineMath.h"

typedef std::pair<const char*, CVector3> InputAxisPair;
typedef std::unordered_map<ui32, InputAxisPair> InputAxisMap;

class CInputMapping
{
public:
	CInputMapping(CInputMapping const&) = delete;
	CInputMapping& operator=(CInputMapping const&) = delete;

	static std::shared_ptr<CInputMapping> Instance()
	{
		static std::shared_ptr<CInputMapping> s_pInstance{ new CInputMapping };
		return s_pInstance;
	}

	void CreateInputAxis(ui32 ui32KeyCode, const char* szAxisName, CVector3 vecAxisMultiplier);
	InputAxisPair* GetInputAxis(ui32 ui32KeyCode);

	bool HasInputAxis(ui32 ui32KeyCode);

private:
	CInputMapping() {}

	bool HasKeyMapping(ui32 ui32KeyCode);

private:
	InputAxisMap m_inputMap;
};