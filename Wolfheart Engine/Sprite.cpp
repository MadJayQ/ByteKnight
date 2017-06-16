#include "Sprite.h"
#include "AssetLoader.h"

#include <cassert>
CSprite::CSprite(
	const char * szFileName, 
	SPRITE_FILE_TYPE fileType
)
{
	Internal_LoadTexture(
		szFileName,
		fileType
	);

}

CSprite::CSprite(
	SDL_Texture* texture
)
{
	m_pTexture = texture;
}

SDL_Surface* CSprite::Internal_LoadBMP(SDL_RWops* file)
{
	return SDL_LoadBMP_RW(file, 1);
}

SDL_Surface* CSprite::Internal_LoadPNG(SDL_RWops* file)
{
	return IMG_LoadTyped_RW(file, 1, "png");
}

void CSprite::Internal_LoadTexture(
	const char* szFileName,
	SPRITE_FILE_TYPE fileType
)
{
	ReleaseTexture();
	SDL_RWops* pFile = SDL_RWFromFile(szFileName, "rb");
	if (pFile == NULL)
	{
		//Log error - File not found
		return;
	}

	SDL_Surface* pLoadedSurface = (fileType == SPRITE_FILE_TYPE_BMP) ? Internal_LoadBMP(pFile) : Internal_LoadPNG(pFile);

	if (pLoadedSurface == NULL) //Failed to load or unsupported file type
	{
		//Log error
		return;
	}
	SDL_Surface* pOptimizedSurface = SDL_ConvertSurfaceFormat(
		pLoadedSurface,
		SDL_PIXELFORMAT_RGBA8888,
		0
	);
	if (pOptimizedSurface == NULL)
	{
		//Log error
		SDL_FreeSurface(pLoadedSurface);
		return;
	}
	CAssetLoader* pAssetLoader = g_pAssetLoader.get();
	assert(pAssetLoader != NULL);
	m_pTexture = pAssetLoader->ConvertToTexture(pOptimizedSurface);
	if (m_pTexture)
	{
		m_nWidth = pOptimizedSurface->w;
		m_nHeight = pOptimizedSurface->h;
	}
	if (pOptimizedSurface) { SDL_FreeSurface(pOptimizedSurface); pOptimizedSurface = NULL; }
}


void CSprite::ReleaseTexture()
{
	if (m_pTexture != NULL)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = NULL;
		m_nWidth = 0;
		m_nHeight = 0;
	}
	if (m_pSurface != NULL)
	{
		SDL_FreeSurface(m_pSurface);
		m_pSurface = NULL;
	}
}