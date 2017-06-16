#pragma once


class CGameWindow
{
public:
	CGameWindow() {}
	~CGameWindow() {}

	void SetWindowName(const char* name) { m_szWindowName = name;  }
	const char* GetWindowName() const { return m_szWindowName; }

	int GetWindowWidth() const { return m_nWindowWidth; }
	int GetWindowHeight() const { return m_nWindowHeight; }

	void SetWindowWidth(int width) { m_nWindowWidth = width; }
	void SetWindowHeight(int height) { m_nWindowHeight = height; }

	void SetWindowSize(int width, int height) { m_nWindowWidth = width; m_nWindowHeight = height; }
	void GetWindowSize(int& width, int& height) { width = m_nWindowWidth; height = m_nWindowHeight; }

protected:
	int m_nWindowWidth;
	int m_nWindowHeight;
	const char* m_szWindowName;
};
