
//Minimalistic Windows Include
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#endif

#include <SDL.h>
#include <SDL_image.h>
#ifdef GAME_INSTANCE
	HINSTANCE g_hInstance;
#endif

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 
#ifdef _DEBUG  
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)  
#else  
#define DEBUG_CLIENTBLOCK  
#endif // _DEBUG  
#ifdef _DEBUG  
#define new DEBUG_CLIENTBLOCK  
#endif  

INT WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
#define SDL_EVENTS_DISABLED 1
#ifdef GAME_INSTANCE
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	g_hInstance = hInstance;
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	int imageSubsystemFlag = IMG_Init(IMG_INIT_PNG);
	if (!(imageSubsystemFlag & IMG_INIT_PNG))
	{
		return -1;
	}
	pEnginePtr->CreateInputMapping();

	pEnginePtr->Initialize();
	int returnCode = pEnginePtr->EngineLoop();
	SDL_Quit();

	return returnCode;
#endif
	return 0;
}





