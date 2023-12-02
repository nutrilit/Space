#include "BitmapHandler.h"

#pragma region Labolatorium5 - zad1
SDL_Texture* BitmapHandler::LoadTexture(const char* NameOfTexture, SDL_Renderer* renderer)
{
    SDL_Surface* Image;
    Image = IMG_Load(NameOfTexture);
    if (!Image) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }

    return SDL_CreateTextureFromSurface(renderer, Image);
}
#pragma endregion

#pragma region Labolatorium5 - zad3
SDL_Texture** BitmapHandler::LoadAnimation(const char* NameOfTexture, SDL_Renderer* renderer, int Frames)
{
    SDL_Texture** Animation = (SDL_Texture**)malloc(Frames * sizeof(SDL_Texture*));

    for (int i = 0; i < Frames; i++)
    {
        char a[1000];
        sprintf_s(a, NameOfTexture, i);
        Animation[i] = LoadTexture(a, renderer);
    }

    return Animation;
}
#pragma endregion
