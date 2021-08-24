#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>

using ComponentID = std::size_t;
constexpr std::size_t maxComponents = 32;

class Entity;
class Component;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

inline ComponentID getUniqueComponentID(void) noexcept
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID(void) noexcept
{
	static_assert(std::is_base_of<Component, T>(), "T must inherit from Component");
	static ComponentID typeID = getUniqueComponentID();
	return typeID;
}

class Component
{
	public:

	Entity* entity = nullptr;

	virtual void init(void) = 0; //Components get initialized upon creation
	virtual void update() = 0; //Manager goes through every entity's components and updates them with the update method (in Game's update)
	virtual void draw(void) = 0; //Manager goes through every entity's components and draws them with the draw method (in Game's render)
	
	virtual ~Component(){};
};

class Entity
{
	private:
		bool active = true;
		bool player = false;
		std::vector<std::unique_ptr<Component>> components; //Used for iteration and ownership checking. Does not contain nullptr's

		ComponentArray componentArray; //Used to actually retrieve a component based on its id. May contain nullptr where there is no component. 
		ComponentBitset componentBitset;

	public:
		void update();
		void draw(void);
		bool isActive(void) const;
		bool isPlayer(void) const;
		void setPlayer(bool);
		void destroy(void);

		template<typename T> bool hasComponent(void) const
		{
			return componentBitset[getComponentTypeID<T>()];
		}

		template<typename T, typename... TArgs>
		T& addComponent(TArgs&&... mArgs)
		{
			assert(!hasComponent<T>());

			T* c = new T(std::forward<TArgs>(mArgs)...);
			c->entity = this;
			std::unique_ptr<Component> uPtr(c);
			components.emplace_back(std::move(uPtr));

			componentArray[getComponentTypeID<T>()] = c;
			componentBitset[getComponentTypeID<T>()] = true;

			c->init();

			return *c;
		}

		template<typename T> T& getComponent() const
		{
			assert(hasComponent<T>());
			auto ptr = componentArray[getComponentTypeID<T>()];
			return *static_cast<T*>(ptr);
		}
};

struct Manager
{
	std::vector<std::unique_ptr<Entity>> entities;

	void update();
	void draw();
	Entity& addEntity();
};