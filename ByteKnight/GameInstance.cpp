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


#include <RenderSubsystem.h>
#include <MovementSubsystem.h>
#include <InputSubsystem.h>
#include <CollisionSubsystem.h>

#include <InputMapping.h> 
#include <UnitMetrics.h>

#include "TestEntity.h"
#include "TestDummy.h"
#include "Defines.h"

#include <Box2D\Box2D.h>

#pragma comment(lib, "Box2D.lib")

constexpr const char* g_szBuildDate = __DATE__;
constexpr const char* g_szBuildTime = __TIME__;

const char* g_szVersion = "Windows Pre-Alpha - v1.0.1a";
const char* g_szClassName = "CLASS_ByteKnight";

std::vector<ui32> ui32Messages;


CEntityBase* ent = 0;


MSG g_lastMessage = MSG{ 0 };

std::unique_ptr<CAssetLoader> g_pAssetLoader;
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
	
	g_pGlobalVars = std::make_unique<CGlobalVars>();
	g_pGlobalVars->ui32Tickrate = 1024;
	g_pGlobalVars->flTickInterval = 1.f / static_cast<float>(g_pGlobalVars->ui32Tickrate);
	g_pGameWorld = std::make_unique<CGameWorld>();
	g_pTimer = std::make_unique<CTimer>();
	m_bLooping = true;
	CUnitMetrics::Instance()->SetPixelsPerMeter(64.f, 1.856); //1.856 is the average high of a male in Meters

	auto pRenderSubsytem = g_pGameWorld->CreateSubsystem<CRenderSubsystem>();
	g_pGameWorld->CreateSubsystem<CMovementSubsystem>();

	pRenderSubsytem->RegisterGraphicsDevice(m_pGraphicsDevice.get());
	pRenderSubsytem->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	
	auto pCollisionSubsystem = g_pGameWorld->CreateSubsystem<CCollisionSubsystem>();
	pCollisionSubsystem->GetCollisionWorld()->SetDebugDraw(
		pRenderSubsytem
	);
	m_pGameWindow->RegisterObserver(
		g_pGameWorld->CreateSubsystem<CInputSubsystem>()
	);

	//Remove this later
	LoadDefaultBackground();
	ent = g_pGameWorld->SpawnEntity<CTestEntity>(v3(391.f, 318.f, 0.f));
	ent->GetComponent<CMovementComponent>()->SetVelocity(v3(500.f, 0.f, 0.f));
	g_pGameWorld->SpawnEntity<CTestDummy>(v3(15.f, 15.f, 0.f));
}

int GameInstance::EngineLoop()
{
	while (m_bLooping)
	{
		if (PeekMessage(&g_lastMessage, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&g_lastMessage);
			DispatchMessage(&g_lastMessage);
			ui32Messages.push_back(g_lastMessage.message);
		}
		SDL_Event e;
		//while (SDL_PollEvent(&e) != 0) {}
		EngineInstance::EngineLoop();
		if (g_lastMessage.message == WM_QUIT)
		{
			m_bLooping = false;
		}
		Sleep(10);
		
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
	CRenderSubsystem* pRenderSubsystem = g_pGameWorld->GetSubsystem<CRenderSubsystem>();
	CCollisionSubsystem* pCollisionSubsystem = g_pGameWorld->GetSubsystem<CCollisionSubsystem>();
	//pRenderSubsystem->Render();
	pCollisionSubsystem->GetCollisionWorld()->DrawDebugData();
	m_pGraphicsDevice->Present();
}

void GameInstance::OnEventNotify(CEntityBase* ent, IEvent* e)
{
	LOCAL_PERSISTENT bool timer = false;
	if (CKeyInputEvent* pEvent = dynamic_cast<CKeyInputEvent*>(e))
	{
		if (pEvent->GetKeyNum() == VK_RETURN)
		{
			if (ButtonState::Pressed(pEvent->GetKeyState()))
			{
				(timer) ? g_pTimer->StopTimer() : g_pTimer->StartTimer();
				timer = !timer;
			}
		}
	}
}

void GameInstance::CreateInputMapping()
{
	CInputMapping::Instance()->CreateInputAxis(0x44, KBMOVEMENTX, v3(1.f, 0.f, 0.f));
	CInputMapping::Instance()->CreateInputAxis(0x41, KBMOVEMENTX, v3(-1.f, 0.f, 0.f));
	CInputMapping::Instance()->CreateInputAxis(0x57, KBMOVEMENTY, v3(0.f, -1.f, 0.f));
	CInputMapping::Instance()->CreateInputAxis(0x53, KBMOVEMENTY, v3(0.f, 1.f, 0.f));
}

void GameInstance::LoadDefaultBackground()
{
	auto ent = g_pGameWorld->SpawnEntity<CEntityBase>();
	auto pPositionComponent = ent->AddComponent<CPositionComponent>();
	pPositionComponent->SetPosition(v3(0.f, 0.f, 0.f));
	auto pRenderComponent = ent->AddComponent<C2DRenderComponent>();
	pRenderComponent->SetSprite(
		new CSprite(
			"Assets\\GameAssets\\Development\\dev_background.png",
			SPRITE_FILE_TYPE::SPRITE_FILE_TYPE_PNG
		)
	);

	g_pGameWorld->GetSubsystem<CRenderSubsystem>()->RegisterEntity(ent);
}
