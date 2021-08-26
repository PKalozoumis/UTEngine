#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "functions.h"
#include "Game.h"

TransformComponent::TransformComponent(int x, int y, int w, int h, int xscale, int yscale)
{
	position.set(static_cast<float>(x),static_cast<float>(y));
	width = w;
	height = h;
	this->xscale = xscale;
	this->yscale = yscale;
}

//========================================= Position =========================================
int TransformComponent::getX(void) const
{
	return static_cast<int>(position.getX());
}

int TransformComponent::getY(void) const
{
	return static_cast<int>(position.getY());
}

void TransformComponent::setX(int xpos)
{
	position.setX(static_cast<float>(xpos));
}

void TransformComponent::setY(int ypos)
{
	position.setY(static_cast<float>(ypos));
}

void TransformComponent::setPos(int xpos, int ypos)
{
	position.setX(static_cast<float>(xpos));
	position.setY(static_cast<float>(ypos));
}

void TransformComponent::addX(int xpos)
{
	position.addX(static_cast<float>(xpos));
}

void TransformComponent::addY(int ypos)
{
	position.addY(static_cast<float>(ypos));
}

void TransformComponent::addXY(int xpos, int ypos)
{
	position.addX(static_cast<float>(xpos));
	position.addY(static_cast<float>(ypos));
}

//========================================= Velocity =========================================
int TransformComponent::getVx(void) const
{
	return static_cast<int>(velocity.getX());
}

int TransformComponent::getVy(void) const
{
	return static_cast<int>(velocity.getY());
}

void TransformComponent::setVx(int x)
{
	velocity.setX(static_cast<float>(x));
}

void TransformComponent::setVy(int y)
{
	velocity.setY(static_cast<float>(y));
}

void TransformComponent::setV(int x, int y)
{
	velocity.setX(static_cast<float>(x));
	velocity.setY(static_cast<float>(y));
}

//========================================= Speed =========================================

void TransformComponent::setSpd(int spd)
{
	this->spd = spd;
}

int TransformComponent::getSpd(void) const
{
	return spd;
}

//==================================== Width/ Height ====================================
int TransformComponent::getWidth(void) const
{
	return width;
}

int TransformComponent::getHeight(void) const
{
	return height;
}

void TransformComponent::setWidth(int width)
{
	if(forcedWidth == -1)
	{
		this->width = width*xscale;
	}
	else this->width = forcedWidth*xscale;
}

void TransformComponent::setHeight(int height)
{
	if(forcedHeight == -1)
	{
		this->height = height*yscale;
	}
	else this->height = forcedHeight*yscale;
}

int TransformComponent::getForcedWidth(void) const
{
	return forcedWidth;
}

int TransformComponent::getForcedHeight(void) const
{
	return forcedHeight;
}

void TransformComponent::setForcedWidth(int width)
{
	forcedWidth = width;
}

void TransformComponent::setForcedHeight(int height)
{
	forcedHeight = height;
}

//======================================== Scale ========================================
int TransformComponent::getXscale(void) const
{
	return xscale;
}

int TransformComponent::getYscale(void) const
{
	return yscale;
}

void TransformComponent::setXscale(int xscale)
{
	this->xscale = xscale;
}

void TransformComponent::setYscale(int yscale)
{
	this->yscale = yscale;
}

void TransformComponent::setScale(int scale)
{
	xscale = scale;
	yscale = scale;
}

void TransformComponent::init(void)
{
	velocity.set(0,0);
}

void TransformComponent::update(void)
{
	if((velocity.getX()!=0)||(velocity.getY()!=0))
	{
		moveTime++;
	}
	else resetMoveTime();

	position.addX(velocity.getX()*spd);
	position.addY(velocity.getY()*spd);
}

void TransformComponent::draw(void)
{
}

void TransformComponent::resetMoveTime(void)
{
	moveTime = 0;
}

int TransformComponent::getMoveTime(void) const
{
	return moveTime;
}

void TransformComponent::print(void) const
{
	std::cout << position << std::endl;
}