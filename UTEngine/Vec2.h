#pragma once

#include <iostream>

struct Vec2
{
		float x,y;

		Vec2(float x = 0.0f, float y = 0.0f);

		Vec2 operator+(const Vec2&) const;
		Vec2 operator-(const Vec2&) const;
		Vec2 operator*(const Vec2&) const;
		Vec2 operator/(const Vec2&) const;

		void operator+=(const Vec2&);
		void operator-=(const Vec2&);
		void operator*=(const Vec2&);
		void operator/=(const Vec2&);
		void operator=(const Vec2&);

		void set(float x, float y);

		float getX(void) const;
		float getY(void) const;

		void setX(float);
		void setY(float);

		void addX(float);
		void addY(float);

		friend std::ostream& operator<<(std::ostream&, const Vec2&);
};

