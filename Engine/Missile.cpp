#include "Missile.h"

Missile::Missile()
	:
	missileFrames(L"missile\\", 5),
	missileAnim(missileFrames, 2.0f)
{}
