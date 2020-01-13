#include "World.h"

World::World()
{
}

void World::addEntity(const std::shared_ptr<Entity>& entity)
{
	_entities.push_back(entity);
}

void World::init()
{
	for (auto& entity : _entities)
		entity->init();
}

void World::update()
{
	for (auto& entity : _entities)
		entity->update();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& entity : _entities)
		target.draw(*entity);
}