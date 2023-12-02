#include "BitmapObject.h"

void BitmapObject::Draw(SDL_Renderer* renderer, SDL_Texture* Texture, SDL_Rect& rect)
{
	SDL_RenderCopy(renderer, Texture, NULL, &rect);
}

void BitmapObject::Draw(SDL_Renderer* renderer, SDL_Rect rect1, SDL_Color color)
{
	int i = 0;
}

