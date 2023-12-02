#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <stdbool.h>
#include <SDL_image.h>

class BitmapHandler
{
public: SDL_Texture* LoadTexture(const char* NameOfTexture, SDL_Renderer* renderer); //wczytaj teksture 
public: SDL_Texture** LoadAnimation(const char* NameOfTexture, SDL_Renderer* renderer, int Frames); //wczytaj animacje
};
