#pragma once

#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF( float X, float Y, float Width, float Height );
	RectF( const Vec2 &TopLeft, const Vec2 &BottomRight );
	bool Overlaps( const RectF &Rect )const;
	
	float GetWidth()const;
	float GetHeight()const;
	Vec2 GetCenter()const;
	float GetCenterX()const;
	float GetCenterY()const;

public:
	float left, top, right, bottom;
};