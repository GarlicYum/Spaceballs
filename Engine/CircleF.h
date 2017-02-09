#pragma once

#include "Vec2.h"

class CircleF
{
public:
	CircleF() = default;
	CircleF( float X, float Y, float R );
	CircleF( const Vec2 &Center, float R );

	bool ContainsPoint( const Vec2 &P );
	bool Overlaps( const CircleF &Cr );

public:
	Vec2 center = { 0.f, 0.f };
	float radius = 1.f;
};

