#include "RectF.h"

RectF::RectF( float X, float Y, float Width, float Height )
	:
	left( X ), top( Y ),
	right( X + Width ), bottom( Y + Height )
{}

RectF::RectF( const Vec2 & TopLeft, const Vec2 & BottomRight )
	:
	left( TopLeft.x ),
	top( TopLeft.y ),
	right( BottomRight.x ),
	bottom( BottomRight.y )
{}

bool RectF::Overlaps( const RectF & Rect ) const
{
	return
		( ( left <= Rect.right ) && ( right >= Rect.left ) ) &&
		( ( top <= Rect.bottom ) && ( bottom >= Rect.top ) );
}

float RectF::GetWidth() const
{
	return right - left;
}

float RectF::GetHeight() const
{
	return bottom - top;
}

Vec2 RectF::GetCenter() const
{
	return Vec2( GetCenterX(), GetCenterY() );
}

float RectF::GetCenterX() const
{
	return left + ( GetWidth() * .5f );
}

float RectF::GetCenterY() const
{
	return top + ( GetHeight() * .5f );
}
