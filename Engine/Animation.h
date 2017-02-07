#pragma once
#include "Surface.h"
#include <string>
#include "Graphics.h"

class Animation
{
public:
	Animation();
	Surface* GetExplo();
private:
	static constexpr int surfCount = 16;
	Surface explo[surfCount];
};