#pragma once

#include <iostream>

template <typename T>
struct Vec2
{
	T x,y;

	Vec2(T x = 0, T y = 0)
	{
		this->x = x;
		this->y = y;
	}

	Vec2 operator+(const Vec2& vec) const
	{
		Vec2 tempVec(x + vec.x, y + vec.y);

		return tempVec;
	}

	Vec2 operator-(const Vec2& vec) const
	{
		Vec2 tempVec(x - vec.x, y - vec.y);

		return tempVec;
	}

	Vec2 operator*(const Vec2& vec) const
	{
		Vec2 tempVec(x * vec.x, y * vec.y);

		return tempVec;
	}

	Vec2 operator/(const Vec2& vec) const
	{
		Vec2 tempVec(x / vec.x, y / vec.y);

		return tempVec;
	}

	void operator+=(const Vec2& vec)
	{
		x += vec.x;
		y += vec.y;
	}

	void operator-=(const Vec2& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}

	void operator*=(const Vec2& vec)
	{
		x *= vec.x;
		y *= vec.y;
	}

	void operator/=(const Vec2& vec)
	{
		x /= vec.x;
		y /= vec.y;
	}

	void operator=(const Vec2& vec)
	{
		x = vec.x;
		y = vec.y;
	}

	void set(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	T getX(void) const
	{
		return x;
	}

	T getY(void) const
	{
		return y;
	}

	void setX(T x)
	{
		this->x = x;
	}

	void setY(T y)
	{
		this->y = y;
	}

	void addX(T x)
	{
		this->x += x;
	}

	void addY(T y)
	{
		this->y += y;
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vec2<T>& vec)
{
	out << "<" << vec.x << ", " << vec.y << ">";
	return out;
}

