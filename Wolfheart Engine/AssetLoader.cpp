#include "AssetLoader.h"
#include "EngineMath.h"

CAssetLoader::CAssetLoader(CGraphicsDevice* device)
{
	m_pGraphicsDevice = device;
}

CAssetLoader::~CAssetLoader()
{
}

SDL_Texture* CAssetLoader::GetTexture(const char* fileName)
{
	return m_textureMap[fileName];
}

SDL_Texture* CAssetLoader::ConvertToTexture(SDL_Surface * surface)
{
	auto pHardwareRenderer = m_pGraphicsDevice->GetHardwareRenderer();
	if (!pHardwareRenderer) m_pGraphicsDevice->CreateRenderer();
	auto pHardwareTexture = SDL_CreateTexture(
		pHardwareRenderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		surface->w,
		surface->h
	);

	SDL_SetTextureBlendMode(
		pHardwareTexture,
		SDL_BLENDMODE_BLEND
	);

	void* data;
	int pitch;

	SDL_Rect clippingRect = surface->clip_rect;

	SDL_LockTexture(
		pHardwareTexture,
		&surface->clip_rect,
		&data,
		&pitch
	);

	memcpy(
		(void*)data,
		(void*)surface->pixels,
		surface->pitch * surface->h
	);

	ui32* pixels = reinterpret_cast<ui32*>(data);
	ui32 ui32PixelCount = (pitch / 4) * clippingRect.h;

	ui32 ui32ColorKey = SDL_MapRGB(
		surface->format,
		0x00,
		0xFF,
		0xFF
	);

	ui32 ui32Transparency = SDL_MapRGBA(
		surface->format,
		0x00,
		0xFF,
		0xFF,
		0xFF
	);

	for (ui32 ui32Pixel = 0; ui32Pixel < ui32PixelCount; ui32Pixel++)
	{
		if (pixels[ui32Pixel] == ui32ColorKey)
		{
			pixels[ui32Pixel] = ui32Transparency;
		}
	}

	SDL_UnlockTexture(pHardwareTexture);
	SDL_FreeSurface(surface);
	return pHardwareTexture;
}

CSprite* CAssetLoader::CreateSprite(const char* name, const char* szFileName, SPRITE_FILE_TYPE type)
{
	return nullptr;
}
