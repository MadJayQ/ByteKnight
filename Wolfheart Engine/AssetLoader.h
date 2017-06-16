#pragma once
#include <unordered_map>
#include <memory>

#include "Sprite.h"
#include "GraphicDevice.h"

class CAssetLoader
{
public:
	CAssetLoader(CGraphicsDevice* device);
	~CAssetLoader();

	SDL_Texture* GetTexture(const char* name);
	SDL_Texture* ConvertToTexture(SDL_Surface* surface);
	CSprite* CreateSprite(const char* name, const char* szFileName, SPRITE_FILE_TYPE type);



private:
	CGraphicsDevice* m_pGraphicsDevice;
	std::unordered_map<const char*, SDL_Texture*> m_textureMap;

}; extern std::unique_ptr<CAssetLoader> g_pAssetLoader;
