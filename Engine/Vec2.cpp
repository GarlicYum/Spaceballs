#include "Vec2.h"
#include <cmath>

Vec2::Vec2(float x_in, float y_in)
	:
	x(x_in),
	y(y_in)
{
}

Vec2 Vec2::operator+(const Vec2 & rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-( const Vec2 & rhs ) const
{
	return Vec2( x - rhs.x, y - rhs.y );
}

Vec2 & Vec2::operator+=(const Vec2 & rhs)
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator*(float rhs) const
{
	return Vec2(x * rhs, y * rhs);
}

Vec2 & Vec2::operator*=(float rhs)
{
	return *this = *this * rhs;
}

float Vec2::SqLength() const
{
	return ( x * x ) + ( y * y );
}

float Vec2::Length() const
{
	return std::sqrtf( SqLength() );
}

Vec2 & Vec2::Normalize()
{
	const float len = Length();
	const float mul = len != 0.f ? 1.f / len : 0.f;
	return *this *= mul;
}

Vec2 Vec2::Normalize() const
{
	return Vec2( *this ).Normalize();
}
