#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <stdbool.h>
#include <SDL_image.h>

class BitmapHandler
{
	/**
* @brief £aduje pojedyncz¹ teksturê z pliku graficznego.
*
* @param NameOfTexture Œcie¿ka do pliku tekstury.
* @param renderer WskaŸnik do SDL_Renderer u¿ywanego do tworzenia tekstury.
* @return WskaŸnik do za³adowanej tekstury SDL_Texture.
*/
public: SDL_Texture* LoadTexture(const char* NameOfTexture, SDL_Renderer* renderer); //wczytaj teksture 

      /**
* @brief  £aduje animacjê jako tablicê wskaŸników SDL_Texture.
*
* Funkcja zak³ada, ¿e klatki animacji s¹ nazwane sekwencyjnie z indeksem jako czêœci¹ nazwy pliku.
* Na przyk³ad, jeœli NameOfTexture to "animacja/klatka_", zostan¹ za³adowane "animacja/klatka_0", "animacja/klatka_1", itd.
*
* @param NameOfTexture Bazowa nazwa klatek animacji.
* @param renderer WskaŸnik do SDL_Renderer u¿ywanego do tworzenia tekstury.
* @param Frames Liczba klatek w animacji.
* @return Tablica wskaŸników SDL_Texture reprezentuj¹ca klatki animacji.
*/
public: SDL_Texture** LoadAnimation(const char* NameOfTexture, SDL_Renderer* renderer, int Frames); //wczytaj animacje
};
