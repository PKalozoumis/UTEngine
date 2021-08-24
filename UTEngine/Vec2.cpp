#include "Vec2.h"

Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2 Vec2::operator+(const Vec2& vec) const
{
	Vec2 tempVec(x + vec.x, y + vec.y);

	return tempVec;
}

Vec2 Vec2::operator-(const Vec2& vec) const
{
	Vec2 tempVec(x - vec.x, y - vec.y);

	return tempVec;
}

Vec2 Vec2::operator*(const Vec2& vec) const
{
	Vec2 tempVec(x * vec.x, y * vec.y);

	return tempVec;
}

Vec2 Vec2::operator/(const Vec2& vec) const
{
	Vec2 tempVec(x / vec.x, y / vec.y);

	return tempVec;
}

void Vec2::operator+=(const Vec2& vec)
{
	x += vec.x;
	y += vec.y;
}

void Vec2::operator-=(const Vec2& vec)
{
	x -= vec.x;
	y -= vec.y;
}

void Vec2::operator*=(const Vec2& vec)
{
	x *= vec.x;
	y *= vec.y;
}

void Vec2::operator/=(const Vec2& vec)
{
	x /= vec.x;
	y /= vec.y;
}

void Vec2::operator=(const Vec2& vec)
{
	x = vec.x;
	y = vec.y;
}

void Vec2::set(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vec2::getX(void) const
{
	return x;
}

float Vec2::getY(void) const
{
	return y;
}

void Vec2::setX(float x)
{
	this->x = x;
}

void Vec2::setY(float y)
{
	this->y = y;
}

void Vec2::addX(float x)
{
	this->x += x;
}

void Vec2::addY(float y)
{
	this->y += y;
}

std::ostream& operator<<(std::ostream& out, const Vec2& vec)
{
	out << "<" << vec.x << ", " << vec.y << ">";
	return out;
}