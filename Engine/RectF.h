#pragma once

class RectF
{
public:
	RectF() = default;
	RectF( float X, float Y, float Width, float Height );

	bool Overlaps( const RectF &Rect )const;
	
	float GetWidth()const;
	float GetHeight()const;
	float GetCenterX()const;
	float GetCenterY()const;

public:
	float left, top, right, bottom;
};