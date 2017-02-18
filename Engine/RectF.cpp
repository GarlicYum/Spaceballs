#include "RectF.h"

RectF::RectF(Vec2& pos, float Width, float Height)
	:
	left(pos.x), top(pos.y),
	right (pos.x + Width), bottom(pos.y + Height)
{}

RectF::RectF(const Vec2& pos, float Width, float Height)
	:
	left(pos.x), top(pos.y),
	right(pos.x + Width), bottom(pos.y + Height)
{}

bool RectF::Overlaps(const RectF& Rect) const
{
	return
		((left <= Rect.right) && (right >= Rect.left)) &&
		((top <= Rect.bottom) && (bottom >= Rect.top));
}

float RectF::GetWidth() const
{
	return right - left;
}

float RectF::GetHeight() const
{
	return bottom - top;
}

float RectF::GetCenterX() const
{
	return left + (GetWidth() * +.5F);
}

float RectF::GetCenterY() const
{
	return top + (GetHeight() * 0.5f);
}

Vec2 RectF::GetCenter() const
{
	return Vec2(GetCenterX(), GetCenterY());
}
