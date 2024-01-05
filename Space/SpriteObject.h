#pragma once
#include <SDL.h>
#include "AnimatedObject.h"
#include "BitmapObject.h"
/**
 * @brief Klasa reprezentuj¹ca obiekt sprite'a.
 *
 * Klasa ta dziedziczy zarówno po klasie AnimatedObject, umo¿liwiaj¹cej animowanie obiektów,
 * jak i po BitmapObject, obs³uguj¹cej obiekty graficzne korzystaj¹ce z bitmap.
 */
class SpriteObject : public AnimatedObject, public BitmapObject
{
};

