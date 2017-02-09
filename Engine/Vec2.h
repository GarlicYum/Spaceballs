#pragma once

class Vec2
{
public:
	Vec2() = default;
	Vec2(float x_in, float y_in);
	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-( const Vec2& rhs )const;
	Vec2& operator+=(const Vec2& rhs);
	Vec2 operator*(float rhs) const;
	Vec2& operator*=(float rhs);

	float SqLength()const;
	float Length()const;
	Vec2& Normalize();
	Vec2 Normalize()const;
public:
	float x;
	float y;
};