#include "GameInstance.h"
#include <Engine.h>
#define GAME_INSTANCE
#include <Windows_EntryPoint.cpp>
#include <AssetLoader.h>
#include <Sprite.h>
#include <TextureUtils.h>
#include <iostream>
#include <cassert>
#include <Timer.h>
#include <Defines.h>
#include <GameWorld.h>
#include <GlobalVars.h>
#include <DummyEvent.h>

constexpr const char* g_szBuildDate = __DATE__;
constexpr const char* g_szBuildTime = __TIME__;

const char* g_szVersion = "Windows Pre-Alpha - v1.0";
const char* g_szClassName = "CLASS_ByteKnight";


MSG g_lastMessage = MSG{ 0 };

std::unique_ptr<CAssetLoader> g_pAssetLoader;
std::unique_ptr<CSprite> g_pTestSprite;
std::unique_ptr<CTimer> g_pTimer;
std::unique_ptr<CGameWorld> g_pGameWorld;
std::unique_ptr<CGlobalVars> g_pGlobalVars;


float flAccumulatedTime = 0.f;
float flLastTime = 0.f;
constexpr float MAX_TICK_TIME_DELTA = 1.f / 10.f; //1/10th of a second

CGlobalVars* GetGlobalVars()
{
	return g_pGlobalVars.get();
}


GameInstance::GameInstance() : EngineInstance()
{

}

GameInstance::~GameInstance()
{
	EngineInstance::~EngineInstance();
	m_pGameWindow.reset();
	m_pGameWindow.release();
	FreeConsole();
}

void GameInstance::Initialize()
{
#ifdef _DEBUG
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	FILE* pStandardOut;
	freopen_s(
		&pStandardOut,
		"CON",
		"w",
		__acrt_iob_func(1)
	);
#endif

	char szNameBuffer[256] = "";
	sprintf_s(
		szNameBuffer, 
		"ByteKnight - %s : Built: %s @ %s EST", 
		g_szVersion, 
		g_szBuildDate, 
		g_szBuildTime
	);

	std::cout << "[DEBUG SESSION]: " << szNameBuffer << std::endl;
	m_pGameWindow = std::make_unique<CWin32GameWindow>(
		g_hInstance, 
		szNameBuffer, 
		g_szClassName
	);
	m_pGameWindow->RegisterObserver(this);
	m_pGraphicsDevice = std::make_unique<CGraphicsDevice>(
		Platform::Windows::Windows_CreateSDLWindow(m_pGameWindow.get()),
		m_pGameWindow.get()
	);
	m_pGraphicsDevice->CreateRenderer();
	g_pAssetLoader = std::make_unique<CAssetLoader>(m_pGraphicsDevice.get());
	g_pTestSprite = std::make_unique<CSprite>(
		"Assets\\GameAssets\\Development\\test_background.png", 
		SPRITE_FILE_TYPE::SPRITE_FILE_TYPE_PNG
	);
	g_pGlobalVars = std::make_unique<CGlobalVars>();
	g_pGlobalVars->ui32Tickrate = 64;
	g_pGlobalVars->flTickInterval = 1.f / static_cast<float>(g_pGlobalVars->ui32Tickrate);
	g_pGameWorld = std::make_unique<CGameWorld>();
	g_pTimer = std::make_unique<CTimer>();
	g_pTimer->StartTimer();
	m_bLooping = true;
}

int GameInstance::EngineLoop()
{
	while (m_bLooping)
	{
		if (PeekMessage(&g_lastMessage, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&g_lastMessage);
			DispatchMessage(&g_lastMessage);
		}
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {}
		EngineInstance::EngineLoop();
		m_bLooping = g_lastMessage.message != WM_QUIT;
	}
	return 0;
}

void GameInstance::Update()
{
	//Perform world update at a fixed rate, 64 times per second
	float flCurrentTime = g_pTimer->TimeConversion<Microseconds, Milliseconds>(
		g_pTimer->GetCurrentTimeStamp()
	);
	float flTimeDelta = flCurrentTime - flLastTime;
	flLastTime = flCurrentTime;

	flAccumulatedTime += flTimeDelta;
	float flTargetTickTime = g_pGlobalVars->flTickInterval * 1000.f;
	while (flAccumulatedTime >= flTargetTickTime)
	{
		g_pGlobalVars->ui32TickCount++;
		g_pGameWorld->Tick(g_pGlobalVars->flTickInterval);
		flAccumulatedTime -= flTargetTickTime;
	}

	g_pGlobalVars->flInterpolation = flAccumulatedTime / flTargetTickTime;
	g_pGlobalVars->flCurrentTime = flCurrentTime;


}

void GameInstance::Render()
{
	//For now just do our rendering ASAP 
	m_pGraphicsDevice->Clear();
	SDL_Texture* texture = g_pTestSprite->GetTexture();
	assert(texture != NULL);
	SDL_Rect renderingRegion = g_pTestSprite->GetRenderingRect();
	SDL_RenderCopy(
		m_pGraphicsDevice->GetHardwareRenderer(),
		texture,
		NULL,
		&renderingRegion
	);
	m_pGraphicsDevice->Present();
}

void GameInstance::OnEventNotify(Entity* ent, IEvent* e)
{
	if (dynamic_cast<CDummyEvent*>(e))
	{
		std::cout << "[DEBUG]: DUMMY EVENT INTERCEPTED" << std::endl;
	}
	else
	{
		std::cout << "[DEBUG]: UNHANDLED EVENT TYPE INTERCEPTED" << std::endl;
	}
}
