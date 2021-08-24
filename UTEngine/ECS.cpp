#include "ECS.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>

void Entity::update()
{
	for(auto& c : components) c->update();
}

void Entity::draw(void)
{
	for(const auto& c : components) c->draw();
}

bool Entity::isActive(void) const
{
	return active;
}

bool Entity::isPlayer(void) const
{
	return player;
}

void Entity::setPlayer(bool player)
{
	this->player = player;
}


void Entity::destroy(void)
{
	active = false;
}

void Manager::update()
{
	//Clearing all disabled entities

	entities.erase
	(
		std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& ent){return !ent->isActive();}),
		std::end(entities)
	);

	for(auto& e : entities) e->update();
}

void Manager::draw()
{
	for(auto& e : entities) e->draw();
}

Entity& Manager::addEntity()
{
	Entity* e = new Entity();
	std::unique_ptr<Entity> uPtr(e);
	entities.emplace_back(std::move(uPtr));

	return *e;
}