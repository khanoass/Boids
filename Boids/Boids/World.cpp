#include "World.h"

World::World()
{
	_size = { 0, 0 };
	_offset = { 0, 0 };
	_type = Type::Blocking;
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

void World::addBoid(const std::shared_ptr<Boid>& boid)
{
	_boids.push_back(boid);
	_entities.push_back(boid);
	_boidsChanged = true;
}

const sf::Vector2u& World::getSize()
{
	return _size;
}

const sf::Vector2i& World::getOffset()
{
	return _offset;
}

std::vector<std::shared_ptr<Boid>>& World::getBoids()
{
	return _boids;
}

void World::init()
{
	_worldPanel.setPrimitiveType(sf::Quads);
	_worldPanel.resize(4);

	_worldPanel[0].color = sf::Color(180, 180, 180);
	_worldPanel[1].color = sf::Color(180, 180, 180);
	_worldPanel[2].color = sf::Color(180, 180, 180);
	_worldPanel[3].color = sf::Color(180, 180, 180);

	_worldPanel[0].position = { (float)_offset.x, (float)_offset.y };
	_worldPanel[1].position = { (float)_offset.x + _size.x, (float)_offset.y };
	_worldPanel[2].position = { (float)_offset.x + _size.x, (float)_offset.y + _size.y };
	_worldPanel[3].position = { (float)_offset.x, (float)_offset.y + _size.y };

	for (auto& boid : _boids)
		boid->setPopulation(_boids);

	for (auto& entity : _entities)
		entity->init();
}

void World::update()
{
	if (_boidsChanged)
	{
		_boidsChanged = false;
		for (auto& boid : _boids)
			boid->setPopulation(_boids);
	}

	for (auto& entity : _entities)
		entity->update();

	switch (_type)
	{
	case Type::Blocking:
		break;
	case Type::Mirrored:

		for (auto& boid : _boids)
		{
			if (boid->getPosition().x > _size.x + _offset.x)
			{
				boid->setPosition({ (float)_offset.x, boid->getPosition().y });
			}
			else if (boid->getPosition().x < +_offset.x)
			{
				boid->setPosition({ (float)(_size.x + _offset.x), boid->getPosition().y });
			}
			else if (boid->getPosition().y > _size.y + _offset.y)
			{
				boid->setPosition({ boid->getPosition().x, (float)_offset.y });
			}
			else if (boid->getPosition().y < _offset.y)
			{
				boid->setPosition({ boid->getPosition().x, (float)(_size.y + _offset.y) });
			}
		}

		break;
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_worldPanel);

	for (const auto& entity : _entities)
		target.draw(*entity);
}