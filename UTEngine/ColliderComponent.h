#pragma once
#include "ECS.h"
#include "SDL.h"
#include "TransformComponent.h"
#include <string>
#include "Vec2.h"

class ColliderComponent : public Component
{
	private:
		Vec2 pos;

	public:
		ColliderComponent():pos(0,0){};

		SDL_Rect collider;
		std::string tag;
		TransformComponent* transform;

		void setX(int x);
		void setY(int y);
		void set(int x, int y);

		const SDL_Rect* const getCollider(void) const;

		void init(void);
		void update(void);
		void draw(void);
};

