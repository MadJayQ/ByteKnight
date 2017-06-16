#include "TextureUtils.h"
#include <memory>
void Utils::Texture::GetTextureSize(SDL_Texture* tex, int& width , int& height)
{
	SDL_Rect clippingRect;
	void* pPixelData;
	int nPitch;
	SDL_LockTexture(
		tex,
		&clippingRect,
		&pPixelData,
		&nPitch
	);

	width = clippingRect.w;
	height = clippingRect.h;

	SDL_UnlockTexture(tex);
}
