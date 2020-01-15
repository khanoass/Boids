#pragma once

#include "Boid.h"

class World : public sf::Drawable
{
public:
	World();

	enum Type { Mirrored, Blocking };

	void create(sf::Vector2u size, sf::Vector2i offset, Type type);

	void addEntity(const std::shared_ptr<Entity>& entity);
	void addBoid(const std::shared_ptr<Boid>& boid);

	const sf::Vector2u& getSize();
	const sf::Vector2i& getOffset();

	std::vector<std::shared_ptr<Boid>>& getBoids();

	void init();
	void update();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2u _size;
	sf::Vector2i _offset;
	Type _type;

	std::vector<std::shared_ptr<Entity>> _entities;
	std::vector<std::shared_ptr<Boid>> _boids;

	bool _boidsChanged = false;

	sf::VertexArray _worldPanel;
};