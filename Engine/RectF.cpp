#include "RectF.h"

RectF::RectF(float X, float Y, float Width, float Height)
	:
	left(X), top(Y),
	right (X + Width), bottom(Y + Height)
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
