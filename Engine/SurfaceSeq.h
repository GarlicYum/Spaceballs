#pragma once

#include "Surface.h"
//#include "Colors.h"
//#include "ChiliException.h"
#include <string>

class SurfaceSeq
{
	SurfaceSeq(std::wstring basename, unsigned int nSurfaces, unsigned int nHoldFrames )
	{

	}
private:
	Surface* surfaces;
	unsigned int nSurfaces;
	const unsigned int nHoldFrames;
	const unsigned int curSurface;
};