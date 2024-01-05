#pragma once
#include <iostream>
#include <SDL.h>
#include "BitmapHandler.h"
#include <SDL_image.h>
/**
 * @brief Klasa reprezentuj�ca obiekt graficzny obs�uguj�cy bitmapy.
 *
 * Klasa ta dziedziczy po BitmapHandler, dostarczaj�cej funkcji obs�ugi obraz�w.
 */
class BitmapObject : public BitmapHandler
{
	/**
* @brief Funkcja rysuj�ca obiekt na podstawie tekstury i prostok�ta.
*
* @param renderer Wska�nik do obiektu klasy SDL_Renderer, na kt�rym ma by� rysowany obiekt bitmapowy.
* @param Texture Tekstura, kt�r� ma u�y� obiekt do rysowania.
* @param rect Prostok�t okre�laj�cy pozycj� i rozmiar obiektu na ekranie.
*
* Funkcja ta rysuje obiekt bitmapowy na ekranie, korzystaj�c z danej tekstury i prostok�ta.
*/
public: void Draw(SDL_Renderer* renderer, SDL_Texture* Texture, SDL_Rect& rect);

	  /**
* @brief Funkcja rysuj�ca prostok�t o okre�lonym kolorze.
*
* @param renderer Wska�nik do obiektu klasy SDL_Renderer, na kt�rym ma by� rysowany prostok�t.
* @param rect1 Prostok�t okre�laj�cy pozycj� i rozmiar prostok�ta na ekranie.
* @param color Kolor prostok�ta, okre�lony jako obiekt klasy SDL_Color.
*
* Funkcja ta rysuje prostok�t o zadanym kolorze na ekranie.
*/
	  void Draw(SDL_Renderer* renderer, SDL_Rect rect1, SDL_Color color);
};

