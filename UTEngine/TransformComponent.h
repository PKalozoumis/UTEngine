#pragma once
#include "ECS.h"
#include "Vec2.h"

class TransformComponent : public Component
{
	private:
		Vec2 position;
		Vec2 velocity;

		int spd = 3;
		int moveTime = 0;

		int xscale = 1, yscale = 1;
		int forcedWidth = -1, forcedHeight = -1; //If forcedWidth == -1, then the width is defined by imageWidth
		int width = 32, height = 32;

	public:
		TransformComponent(int x = 0, int y = 0, int w = 32, int h = 32, int xscale = 1, int yscale = 1);
		int getX(void) const;
		int getY(void) const;

		void setX(int);
		void setY(int);
		void setPos(int, int);

		void addX(int);
		void addY(int);
		void addXY(int,int);

		void setVx(int);
		void setVy(int);
		void setV(int, int);

		int getVx(void) const;
		int getVy(void) const;

		int getSpd(void) const;
		void setSpd(int);

		int getXscale(void) const;
		int getYscale(void) const;

		void setXscale(int);
		void setYscale(int);

		int getWidth(void) const;
		int getHeight(void) const;

		void setWidth(int);
		void setHeight(int);

		int getForcedWidth(void) const;
		int getForcedHeight(void) const;

		void setForcedWidth(int);
		void setForcedHeight(int);

		void setScale(int);

		void init(void);
		void update(void);
		void draw(void);

		void resetMoveTime(void);
		int getMoveTime(void) const;
};

