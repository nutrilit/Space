#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <stdbool.h>
#include <SDL_image.h>
#include "BitmapHandler.h"

class AnimatedObject : public BitmapHandler
{
public: virtual void animate(SDL_Renderer* renderer, SDL_Texture** Animation, SDL_Rect& rect, int i);
};

