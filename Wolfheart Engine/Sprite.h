#pragma once

#include <SDL.h>
#include <SDL_image.h>

enum SPRITE_FILE_TYPE
{
	SPRITE_FILE_TYPE_BMP = 0,
	SPRITE_FILE_TYPE_PNG,
	SPRITE_FILE_TYPE_DDS,
	SPRITE_FILE_TYPE_GENERIC
};
class CSprite
{
public:
	CSprite(const char* szFileName, SPRITE_FILE_TYPE fileType);
	CSprite(SDL_Texture* texture);

	void ReleaseTexture();
	SDL_Texture* GetTexture() const { return m_pTexture; }

	int GetWidth() const { return m_nWidth; }
	int GetHeight() const { return m_nHeight; }

	SDL_Rect GetRenderingRect() const { return SDL_Rect{ 0, 0, m_nWidth, m_nHeight }; }

private:
	SDL_Surface* Internal_LoadBMP(SDL_RWops* file);
	SDL_Surface* Internal_LoadPNG(SDL_RWops* file);
	void Internal_LoadTexture(const char* szFileName, SPRITE_FILE_TYPE fileType);
private:
	SDL_Surface* m_pSurface = NULL;
	SDL_Texture* m_pTexture = NULL;

	int m_nWidth = 0;
	int m_nHeight = 0;
};
