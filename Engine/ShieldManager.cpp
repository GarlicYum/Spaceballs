#include "ShieldManager.h"
#include "Ship.h"

void ShieldManager::Update(Ship & ship)
{
	shield.Update(ship);
}

void ShieldManager::Draw(Graphics & gfx)
{
	shield.Draw(gfx);
}
