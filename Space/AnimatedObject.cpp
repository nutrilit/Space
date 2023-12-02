#include "AnimatedObject.h"

void AnimatedObject::animate(SDL_Renderer* renderer, SDL_Texture** Animation, SDL_Rect& rect, int i)
{
	SDL_RenderCopy(renderer, Animation[i], NULL, &rect);
}
