#include "Engine.h"

EngineInstance::EngineInstance()
{
}

EngineInstance::~EngineInstance()
{
}

void EngineInstance::Initialize()
{

}

int EngineInstance::EngineLoop()
{
	Update();
	Render();
	return 0;
}
