#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <stdbool.h>
#include <SDL_image.h>
#include "BitmapHandler.h"

/**
 * @brief Klasa reprezentuj�ca obiekt animowany.
 *
 * Klasa ta dziedziczy po klasie BitmapHandler, co umo�liwia korzystanie z funkcji obs�uguj�cych obrazy.
 */
class AnimatedObject : public BitmapHandler
{
	/**
* @brief Wirtualna funkcja do animowania obiektu.
*
* @param renderer Wska�nik do obiektu klasy SDL_Renderer, na kt�rym ma by� rysowany obiekt animowany.
* @param Animation Tablica tekstur reprezentuj�ca animacj�.
* @param rect Prostok�t okre�laj�cy pozycj� i rozmiar obiektu animowanego.
* @param i Numer klatki animacji, kt�r� nale�y wy�wietli�.
*
* Funkcja ta pozwala na animowanie obiektu poprzez wy�wietlanie kolejnych klatek animacji.
*/
public: virtual void animate(SDL_Renderer* renderer, SDL_Texture** Animation, SDL_Rect& rect, int i);
};

