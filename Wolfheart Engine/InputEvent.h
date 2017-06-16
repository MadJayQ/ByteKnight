#pragma once
#include "Event.h"
#include "EngineMath.h"

#define MODIFIER_LSHIFT 1 << 0
#define MODIFIER_LCNTRL 1 << 1
#define MODIFIER_LALT   1 << 2

enum ButtonState
{
	KeyState_Pressed = 0,
	KeyState_Released,
	KeyState_Held
};

/*
	For Keyboard Input
*/

class CKeyInputEvent : IEvent
{
public:
	CKeyInputEvent(int nKeyNum, ui32 ui32Modifiers, ButtonState keyState)
	{
		m_nKeyNum = nKeyNum;

	}
	~CKeyInputEvent() {}

	ui32 GetModifiers() const { return m_ui32Modifiers; }
	int GetKeyNum() const { return m_nKeyNum; }
	ButtonState GetKeyState() const { return m_keyState; }

private:
	int m_nKeyNum;
	ui32 m_ui32Modifiers;
	ButtonState m_keyState;
};


/*
	For Joystick input
*/
class CJoyInputEvent : IEvent
{

};