#include "CircleF.h"



CircleF::CircleF( float X, float Y, float R )
	:
	CircleF( { X,Y }, R )
{
}

CircleF::CircleF( const Vec2 & Center, float R )
	:
	center( Center ),
	radius( R )	
{}

bool CircleF::ContainsPoint( const Vec2 & P )
{
	return ( center - P ).SqLength() <= ( radius * radius );
}

bool CircleF::Overlaps( const CircleF & Cr )
{
	return ( center - Cr.center ).SqLength() <= ( radius + Cr.radius ) * ( radius + Cr.radius );
}
