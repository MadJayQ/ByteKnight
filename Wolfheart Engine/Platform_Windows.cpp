#include "Platform_Windows.h"
#include "DummyEvent.h"
#include "InputEvent.h"

#include <cassert>
#include <iostream>

#define WINSTYLE (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX))

CWin32GameWindow* This = NULL;

namespace Window
{
	size_t WINDOW_WIDTH = 1280;
	size_t WINDOW_HEIGHT = 720;
}

VOID WINAPI SetClientSize(HWND hWnd,
	size_t nWidth,
	size_t nHeight
)
{
	RECT rc;

	GetClientRect(hWnd, &rc);
	nWidth -= rc.right;
	nHeight -= rc.bottom;

	GetWindowRect(hWnd, &rc);

	nWidth += (rc.right - rc.left);
	nHeight += (rc.bottom - rc.top);

	SetWindowPos(hWnd, NULL, 0, 0, nWidth, nHeight, SWP_NOMOVE);
}


HRESULT WINAPI RegisterWindow(HINSTANCE hInstance,
	WNDPROC wndProc,
	HWND& hWnd,
	LPCSTR lpszClassName,
	LPCSTR lpszWindowName
)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = static_cast<WNDPROC>(wndProc);
	wcex.lpszClassName = lpszClassName;
	wcex.lpszMenuName = 0;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

	if (!RegisterClassEx(&wcex))
	{
		return E_FAIL;
	}

	RECT rc = { 0, 0, Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT };
	AdjustWindowRect(&rc, WINSTYLE, TRUE);

	hWnd = CreateWindowEx(NULL,
		lpszClassName,
		lpszWindowName,
		WINSTYLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right, //Adjusted Width
		rc.bottom, //Adjusted Height
		NULL,
		NULL,
		hInstance,
		NULL
	);

	SetClientSize(hWnd, Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT);

	if (hWnd == NULL)
	{
		return E_FAIL;
	}

	return S_OK;
}
CWin32GameWindow::CWin32GameWindow(HINSTANCE hInstance, const char* szWindowName, const char* szClassName) :
	m_hInstance(hInstance),
	m_szWindowName(szWindowName),
	m_szClassName(szClassName)
{
	CGameWindow::m_nWindowHeight = 1280;
	CGameWindow::m_nWindowWidth = 720;
	CGameWindow::m_szWindowName = szWindowName;
	RegisterWindow(m_hInstance, CWin32GameWindow::MessageProcedureLoop, m_hWnd, m_szClassName, m_szWindowName);
	This = this;
	HRESULT result = ShowWindow(m_hWnd, 10);
	if (FAILED(result))
	{
		assert(false);
	}

	assert(CreateRawInputDevices());

	memset(
		(void*)m_bPreviousKeyState,
		false,
		512
	);

	memset(
		(void*)m_bCurrentKeyState,
		false,
		512
	);

}

CWin32GameWindow::~CWin32GameWindow()
{

}

LRESULT CWin32GameWindow::MessageProcedureLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
	{
		break;
	}
	case WM_DESTROY:
	{
		std::cout << "[DEBUG]: DUMMY EVENT POSTED FROM OS LOOP" << std::endl;
		This->EventNotify(0, new CDummyEvent());
		PostQuitMessage(0);
		break;
	}
	case WM_INPUT:
	{
		ui32 ui32Size = sizeof(RAWINPUT);
		ui8 ui8Buffer[sizeof(RAWINPUT)] = {};

		GetRawInputData(
			reinterpret_cast<HRAWINPUT>(lParam),
			RID_INPUT,
			ui8Buffer,
			&ui32Size,
			sizeof(RAWINPUTHEADER)
		);

		RAWINPUT* pRawInput = reinterpret_cast<RAWINPUT*>(ui8Buffer);
		if (pRawInput->header.dwType == RIM_TYPEKEYBOARD)
		{
			MappedVirtualKey_t keyData;
			if (This->MapCorrectVirtualKey(ui8Buffer, &keyData))
			{
				This->FireKeyEvent(&keyData);
			}
		}

		break;

	}
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool CWin32GameWindow::CreateRawInputDevices()
{
	RAWINPUTDEVICE inputDevices[4];
	int nNumInputDevices = 4;
	size_t dwInputDeviceSize = sizeof(RAWINPUTDEVICE);

	inputDevices[0].usUsagePage = 0x1;
	inputDevices[0].usUsage = 0x2;
	inputDevices[0].dwFlags = 0x0;
	inputDevices[0].hwndTarget = m_hWnd;

	inputDevices[1].usUsagePage = 0x01;
	inputDevices[1].usUsage = 0x06;
	inputDevices[1].dwFlags = RIDEV_NOLEGACY;
	inputDevices[1].hwndTarget = m_hWnd;

	inputDevices[2].usUsagePage = 0x01;
	inputDevices[2].usUsage = 0x05;
	inputDevices[2].dwFlags = 0x0;
	inputDevices[2].hwndTarget = m_hWnd;

	inputDevices[3].usUsagePage = 0x01;
	inputDevices[3].usUsage = 0x04;
	inputDevices[3].dwFlags = 0x0;
	inputDevices[3].hwndTarget = m_hWnd;

	if (RegisterRawInputDevices(inputDevices, nNumInputDevices, dwInputDeviceSize) == FALSE)
	{
#ifdef _DEBUG
		std::cout << "[DEBUG]: FAILED TO REGISTER RAW INPUT DEVICES! " << GetLastError() << std::endl;
#endif
		return false;
	}

	return true;
}

bool CWin32GameWindow::MapCorrectVirtualKey(void* pInputBuffer, MappedVirtualKey_t* keyData)
{
	RAWKEYBOARD* pKeyboardData = &reinterpret_cast<RAWINPUT*>(pInputBuffer)->data.keyboard;
	ui32 ui32VirtualKey = pKeyboardData->VKey;
	ui32 ui32ScanCode = pKeyboardData->MakeCode;
	ui32 ui32Flags = pKeyboardData->Flags;

	bool bIsModifier = false;

	//These are our non-corrected datum
	keyData->m_oldValues.m_ui32ScanCode = ui32ScanCode;
	keyData->m_oldValues.m_ui32VirtualKey = ui32VirtualKey;
	keyData->m_oldValues.m_ui32Flags = ui32Flags;

	//Discard windows garbage ghost keys
	if (ui32VirtualKey == 0xFF) 
	{
		return false; 
	}
	else if (ui32VirtualKey == VK_SHIFT)
	{
		ui32VirtualKey = MapVirtualKey(
			ui32ScanCode,
			MAPVK_VSC_TO_VK
		);

		bIsModifier = true;
	}
	else if (ui32VirtualKey == VK_NUMLOCK)
	{
		ui32ScanCode = MapVirtualKey(
			ui32VirtualKey,
			MAPVK_VK_TO_VSC_EX
		);
		ui32ScanCode |= 0x100;
	}

	const bool e0 = ((ui32Flags & RI_KEY_E0) != 0);
	const bool e1 = ((ui32Flags & RI_KEY_E1) != 0);

	if (e1)
	{
		if (ui32VirtualKey == VK_PAUSE)
		{
			ui32ScanCode = 0x45;
		}
		else
		{
			ui32ScanCode = MapVirtualKey(
				ui32VirtualKey,
				MAPVK_VK_TO_VSC_EX
			);
		}
	}

	switch (ui32VirtualKey)
	{
		case VK_CONTROL:
		{
			ui32VirtualKey = (e0) ? VK_RCONTROL : VK_LCONTROL;
			bIsModifier = true;
			break;
		}
		case VK_MENU:
		{
			ui32VirtualKey = (e0) ? VK_RMENU : VK_LMENU;
			bIsModifier = true;
			break;
		}
	}

	keyData->m_correctedValues.m_ui32VirtualKey = ui32VirtualKey;
	keyData->m_correctedValues.m_ui32ScanCode = ui32ScanCode;
	
	const bool pressed = ((ui32Flags & RI_KEY_BREAK) == 0);
	ui32 ui32KeyCode = (ui32ScanCode << 16) | (e0 << 24);

	char buffer[512] = {};
	GetKeyNameText(
		ui32KeyCode,
		buffer,
		512
	);

	keyData->m_extendedData.m_szKeyName = buffer;
	keyData->m_extendedData.m_ui32KeyCode = ui32KeyCode;
	keyData->m_extendedData.m_bPressed = pressed;
	keyData->m_extendedData.m_bModifierKey = bIsModifier;

	return true;
}

void CWin32GameWindow::FireKeyEvent(MappedVirtualKey_t* keyData)
{

	ui32 ui32VirtualKey = keyData->m_correctedValues.m_ui32VirtualKey;
	m_bCurrentKeyState[ui32VirtualKey] = keyData->m_extendedData.m_bPressed;

	ButtonState buttonState;
	ui32 ui32KeyModifers = 0;

	CKeyInputEvent* e = NULL;

	buttonState = ButtonState::KeyState_Released;

	if (m_bCurrentKeyState[ui32VirtualKey] && m_bPreviousKeyState[ui32VirtualKey])
	{
		buttonState = ButtonState::KeyState_Held;
	}

	if (m_bCurrentKeyState[ui32VirtualKey] && !m_bPreviousKeyState[ui32VirtualKey])
	{
		buttonState = ButtonState::KeyState_Pressed;
	}

	if (!keyData->m_extendedData.m_bModifierKey)
	{
		if (m_bCurrentKeyState[VK_LSHIFT]) { ui32KeyModifers |= MODIFIER_LSHIFT; }
		if (m_bCurrentKeyState[VK_LCONTROL]) { ui32KeyModifers |= MODIFIER_LCNTRL; }
		if (m_bCurrentKeyState[VK_LMENU]) { ui32KeyModifers |= MODIFIER_LALT; }

		if (m_bCurrentKeyState[ui32VirtualKey])

			e = new CKeyInputEvent(
				ui32VirtualKey,
				ui32KeyModifers,
				buttonState
			);

	}
	else if (ui32VirtualKey == VK_LSHIFT || ui32VirtualKey == VK_RSHIFT)
	{
		e = new CKeyInputEvent(
			ui32VirtualKey,
			0,
			buttonState
		);
	}

	if (e != NULL)
	{
		EventNotify(NULL, e);
	}



}

SDL_Window * Platform::Windows::Windows_CreateSDLWindow(CWin32GameWindow* window)
{
	return SDL_CreateWindowFrom(window->GetWindowHandle());
}
