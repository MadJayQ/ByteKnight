#pragma once

#include <Windows.h> //Inlclude entire windows include
#include "GameWindow.h"
#include "EventSource.h"

#include <SDL.h>
#include <vector>
#include <queue>


struct MappedVirtualKey_t
{
	struct
	{
		ui32 m_ui32VirtualKey;
		ui32 m_ui32ScanCode;
		ui32 m_ui32Flags;
	} m_oldValues;

	struct
	{
		ui32 m_ui32VirtualKey;
		ui32 m_ui32ScanCode;
	} m_correctedValues;

	struct
	{
		const char* m_szKeyName;
		ui32 m_ui32KeyCode;
		bool m_bPressed;
		bool m_bModifierKey;
	} m_extendedData;
};

class CWin32GameWindow : public CGameWindow, public IEventSource
{
public:
	CWin32GameWindow(HINSTANCE hInstance, const char* szWindowName, const char* szClassName);
	CWin32GameWindow() {}
	~CWin32GameWindow();

	static LRESULT CALLBACK MessageProcedureLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND GetWindowHandle() const { return m_hWnd; }

private:
	bool CreateRawInputDevices();
	bool MapCorrectVirtualKey(void* pInputBuffer, MappedVirtualKey_t* keyData);
	void FireKeyEvent(MappedVirtualKey_t* keyData);

private:
	HINSTANCE m_hInstance; //This is our programs handle
	HWND m_hWnd;
	MSG m_msg;

	const char* m_szWindowName = "Wolfheart Windows Game";
	const char* m_szClassName = "WolfheartEngine_Class";


	bool m_bPreviousKeyState[512];
	bool m_bCurrentKeyState[512];

};


namespace Platform
{
	namespace Windows
	{
		SDL_Window* Windows_CreateSDLWindow(CWin32GameWindow* window);
	}
}
