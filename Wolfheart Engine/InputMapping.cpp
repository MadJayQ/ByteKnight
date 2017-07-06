#include "InputMapping.h"

void CInputMapping::CreateInputAxis(ui32 ui32KeyCode, const char* szAxisName, CVector3 vecAxisMultiplier)
{
	m_inputMap[ui32KeyCode] = std::make_pair(
		szAxisName,
		vecAxisMultiplier
	);
}

InputAxisPair* CInputMapping::GetInputAxis(ui32 ui32KeyCode)
{
	return (HasKeyMapping(ui32KeyCode) ? &m_inputMap[ui32KeyCode] : nullptr);
}

bool CInputMapping::HasKeyMapping(ui32 ui32KeyCode)
{
	auto itr = m_inputMap.find(ui32KeyCode);
	return itr != m_inputMap.end();
}
