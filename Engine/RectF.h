#pragma once
#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(Vec2& pos, float Width, float Height);
	RectF(const Vec2& pos, float Width, float Height);
	bool Overlaps(const RectF& Rect) const;
	float GetWidth() const;
	float GetHeight() const;
	float GetCenterX() const;
	float GetCenterY() const;

public:
	float left;
	float top;
	float right;
	float bottom;
};