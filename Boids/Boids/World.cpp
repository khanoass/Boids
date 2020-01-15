#include "World.h"

World::World()
{
}

void World::create(sf::Vector2u size, sf::Vector2i offset, Type type)
{
	_size = size;
	_offset = offset;
	_type = type;
}

void World::addEntity(const std::shared_ptr<Entity>& entity)
{
	_entities.push_back(entity);
}

void World::init()
{
	_worldPanel.setPrimitiveType(sf::Quads);
	_worldPanel.resize(4);

	_worldPanel[0].color = sf::Color(20, 20, 20);
	_worldPanel[1].color = sf::Color(20, 20, 20);
	_worldPanel[2].color = sf::Color(20, 20, 20);
	_worldPanel[3].color = sf::Color(20, 20, 20);

	_worldPanel[0].position = { (float)_offset.x, (float)_offset.y };
	_worldPanel[1].position = { (float)_offset.x + _size.x, (float)_offset.y };
	_worldPanel[2].position = { (float)_offset.x + _size.x, (float)_offset.y + _size.y };
	_worldPanel[3].position = { (float)_offset.x, (float)_offset.y + _size.y };

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
	target.draw(_worldPanel);

	for (const auto& entity : _entities)
		target.draw(*entity);
}