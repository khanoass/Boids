#pragma once

#include "Entity.h"

class Obstacle : public Entity
{
public:
	Obstacle();

	virtual void init();
	virtual void update();

	void setPosition(const sf::Vector2f& position);
	void setRadius(float radius);
	void setColor(const sf::Color& color);

	const sf::Vector2f& getPosition();
	float getRadius();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::CircleShape _shape;

	sf::Color _color;
	sf::Vector2f _position;
	float _radius;
};