#include "GraphicDevice.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

CGraphicsDevice::CGraphicsDevice(
	SDL_Window * window,
	CGameWindow* gameWindow) :
	m_pGameWindow(gameWindow),
	m_pDrawWindow(window)
{

}

CGraphicsDevice::CGraphicsDevice(
	CGameWindow* gameWindow) :
	m_pGameWindow(gameWindow)
{
	m_pDrawWindow = SDL_CreateWindow(
		"Wolfheart Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		720,
		NULL
	);
}

CGraphicsDevice::~CGraphicsDevice()
{
}

void CGraphicsDevice::Present()
{
	SDL_RenderPresent(m_pGameRenderer);
}

void CGraphicsDevice::CreateRenderer()
{
	m_pGameRenderer = SDL_CreateRenderer(
		m_pDrawWindow,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	SDL_SetHint(
		SDL_HINT_RENDER_VSYNC,
		"1"
	);
}

void CGraphicsDevice::Cleanup()
{
	SDL_DestroyRenderer(m_pGameRenderer);
}

void CGraphicsDevice::Clear()
{
	SDL_SetRenderDrawColor(
		m_pGameRenderer,
		 0x00,
		 0x00,
		 0x00,
		 0xFF
	 );
	 SDL_RenderClear(m_pGameRenderer);
}
