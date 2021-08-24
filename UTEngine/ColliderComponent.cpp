#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "functions.h"
#include "ECS.h"
#include "SDL.h"

void ColliderComponent::setX(int x)
{
	pos.setX(static_cast<float>(x));
}

void ColliderComponent::setY(int y)
{
	pos.setY(static_cast<float>(y));
}

void ColliderComponent::set(int x, int y)
{
	pos.setX(static_cast<float>(x));
	pos.setY(static_cast<float>(y));
}

void ColliderComponent::init(void)
{
	if(!entity->hasComponent<TransformComponent>())
	{
		entity->addComponent<TransformComponent>();
	}

	transform = &entity->getComponent<TransformComponent>();
}

void ColliderComponent::update(void)
{
	collider.x = static_cast<int>(pos.getX()) + transform->getX();
	collider.y = static_cast<int>(pos.getY()) + transform->getY();
	collider.w = transform->getWidth()*transform->getXscale();
	collider.h = transform->getHeight()*transform->getYscale();
}

void ColliderComponent::draw(void)
{
	//drawRectangleColor(collider.x, collider.y, collider.x + collider.w, collider.y + collider.h,1,c_red);
}

const SDL_Rect* const ColliderComponent::getCollider(void) const
{
	return &collider;
}