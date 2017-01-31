#include "Shield.h"

void Shield::Update(Ship & ship)
{
	x = ship.GetX() + (ship.GetWidth() / 2);
	y = ship.GetY() + (ship.GetHeight() / 2);
}
