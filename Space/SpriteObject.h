#pragma once
#include <SDL.h>
#include "AnimatedObject.h"
#include "BitmapObject.h"
/**
 * @brief Klasa reprezentuj�ca obiekt sprite'a.
 *
 * Klasa ta dziedziczy zar�wno po klasie AnimatedObject, umo�liwiaj�cej animowanie obiekt�w,
 * jak i po BitmapObject, obs�uguj�cej obiekty graficzne korzystaj�ce z bitmap.
 */
class SpriteObject : public AnimatedObject, public BitmapObject
{
};

