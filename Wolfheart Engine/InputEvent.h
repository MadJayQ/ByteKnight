#pragma once
#include "Event.h"
#include "EngineMath.h"

#define MODIFIER_LSHIFT 1 << 0
#define MODIFIER_LCNTRL 1 << 1
#define MODIFIER_LALT   1 << 2

class ButtonState
{
public:
	enum State
	{
		KeyState_Pressed = 0,
		KeyState_Released,
		KeyState_Held
	};

	static bool Pressed(const ButtonState::State& state)
	{
		return (state == ButtonState::KeyState_Pressed || state == KeyState_Held);
	}
};

/*
	For Keyboard Input
*/

class CKeyInputEvent : public IEvent
{
public:
	CKeyInputEvent(ui32 ui32KeyNum, ui32 ui32Modifiers, ButtonState::State keyState)
	{
		m_ui32KeyNum = ui32KeyNum;
		m_ui32Modifiers = ui32Modifiers;
		m_keyState = keyState;

	}
	~CKeyInputEvent() {}

	ui32 GetModifiers() const { return m_ui32Modifiers; }
	ui32 GetKeyNum() const { return m_ui32KeyNum; }
	ButtonState::State GetKeyState() const { return m_keyState; }

private:
	ui32 m_ui32KeyNum;
	ui32 m_ui32Modifiers;
	ButtonState::State m_keyState;
};


/*
	For Joystick input
*/
class CJoyInputEvent : IEvent
{

};