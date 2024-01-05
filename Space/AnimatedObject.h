#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <stdbool.h>
#include <SDL_image.h>
#include "BitmapHandler.h"

/**
 * @brief Klasa reprezentuj¹ca obiekt animowany.
 *
 * Klasa ta dziedziczy po klasie BitmapHandler, co umo¿liwia korzystanie z funkcji obs³uguj¹cych obrazy.
 */
class AnimatedObject : public BitmapHandler
{
	/**
* @brief Wirtualna funkcja do animowania obiektu.
*
* @param renderer WskaŸnik do obiektu klasy SDL_Renderer, na którym ma byæ rysowany obiekt animowany.
* @param Animation Tablica tekstur reprezentuj¹ca animacjê.
* @param rect Prostok¹t okreœlaj¹cy pozycjê i rozmiar obiektu animowanego.
* @param i Numer klatki animacji, któr¹ nale¿y wyœwietliæ.
*
* Funkcja ta pozwala na animowanie obiektu poprzez wyœwietlanie kolejnych klatek animacji.
*/
public: virtual void animate(SDL_Renderer* renderer, SDL_Texture** Animation, SDL_Rect& rect, int i);
};

