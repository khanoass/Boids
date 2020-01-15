#pragma once

#include "Entity.h"

class World : public sf::Drawable
{
public:
	World();

	enum Type { Mirrored, Blocking };

	void create(sf::Vector2u size, sf::Vector2i offset, Type type);

	void addEntity(const std::shared_ptr<Entity>& entity);

	void init();
	void update();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2u _size;
	sf::Vector2i _offset;
	Type _type;

	std::vector<std::shared_ptr<Entity>> _entities;

	sf::VertexArray _worldPanel;
};