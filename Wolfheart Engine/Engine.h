#pragma once
#include <memory>


#define ENGINE_API __stdcall
#define REGISTER_ENGINE_CLASS(classType) std::unique_ptr<classType> pEnginePtr = std::unique_ptr<classType>(new classType());

class EngineInstance
{
public:
	explicit EngineInstance();
	~EngineInstance();

	virtual void Initialize();
	virtual int EngineLoop();

	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void CreateInputMapping() = 0; //Change this to have engine default input mappings??

protected:
	bool m_bLooping = false;
};
