#pragma once
#include <iostream>
#include <SDL.h>
#include "BitmapHandler.h"
#include <SDL_image.h>

class BitmapObject : public BitmapHandler
{
public: void Draw(SDL_Renderer* renderer, SDL_Texture* Texture, SDL_Rect& rect);
	  void Draw(SDL_Renderer* renderer, SDL_Rect rect1, SDL_Color color);
};

