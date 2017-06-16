#pragma once

#include <SDL.h>
#include "GameWindow.h"

class CGraphicsDevice
{
public:
	CGraphicsDevice(SDL_Window* window, CGameWindow* gameWindow);
	CGraphicsDevice(CGameWindow* gameWindow);
	~CGraphicsDevice();

	void CreateRenderer();
	void Cleanup();
	void Clear();

	void Present();

	SDL_Renderer* GetHardwareRenderer() const { return m_pGameRenderer; }

private:

	SDL_Window* m_pDrawWindow = 0;
	SDL_Renderer* m_pGameRenderer = 0;
	CGameWindow* m_pGameWindow = 0;

};
