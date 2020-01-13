#pragma once

#include "Entity.h"

class Boid : public Entity
{
public:
	Boid();

	virtual void init();
	virtual void update();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::RectangleShape c;
};