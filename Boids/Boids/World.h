#pragma once

#include "Entity.h"

class World : public sf::Drawable
{
public:
	World();

	void addEntity(const std::shared_ptr<Entity>& entity);

	void init();
	void update();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<std::shared_ptr<Entity>> _entities;
};