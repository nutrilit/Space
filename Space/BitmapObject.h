#pragma once
#include <iostream>
#include <SDL.h>
#include "BitmapHandler.h"
#include <SDL_image.h>
/**
 * @brief Klasa reprezentuj¹ca obiekt graficzny obs³uguj¹cy bitmapy.
 *
 * Klasa ta dziedziczy po BitmapHandler, dostarczaj¹cej funkcji obs³ugi obrazów.
 */
class BitmapObject : public BitmapHandler
{
	/**
* @brief Funkcja rysuj¹ca obiekt na podstawie tekstury i prostok¹ta.
*
* @param renderer WskaŸnik do obiektu klasy SDL_Renderer, na którym ma byæ rysowany obiekt bitmapowy.
* @param Texture Tekstura, któr¹ ma u¿yæ obiekt do rysowania.
* @param rect Prostok¹t okreœlaj¹cy pozycjê i rozmiar obiektu na ekranie.
*
* Funkcja ta rysuje obiekt bitmapowy na ekranie, korzystaj¹c z danej tekstury i prostok¹ta.
*/
public: void Draw(SDL_Renderer* renderer, SDL_Texture* Texture, SDL_Rect& rect);

	  /**
* @brief Funkcja rysuj¹ca prostok¹t o okreœlonym kolorze.
*
* @param renderer WskaŸnik do obiektu klasy SDL_Renderer, na którym ma byæ rysowany prostok¹t.
* @param rect1 Prostok¹t okreœlaj¹cy pozycjê i rozmiar prostok¹ta na ekranie.
* @param color Kolor prostok¹ta, okreœlony jako obiekt klasy SDL_Color.
*
* Funkcja ta rysuje prostok¹t o zadanym kolorze na ekranie.
*/
	  void Draw(SDL_Renderer* renderer, SDL_Rect rect1, SDL_Color color);
};

