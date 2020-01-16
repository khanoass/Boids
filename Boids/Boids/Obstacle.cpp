#include "Obstacle.h"

Obstacle::Obstacle()
{
	_position = { 0, 0 };
	_radius = 0;
}

void Obstacle::init()
{
	_shape.setFillColor(sf::Color::Transparent);
	_shape.setOutlineThickness(1);
	_shape.setOutlineColor(_color);
	_shape.setOrigin(_radius, _radius);
	_shape.setRadius(_radius);
	_shape.setPosition(_position);
}

void Obstacle::update()
{
}

void Obstacle::setPosition(const sf::Vector2f& position)
{
	_position = position;
}

void Obstacle::setRadius(float radius)
{
	_radius = radius;
}

void Obstacle::setColor(const sf::Color & color)
{
	_color = color;
}

const sf::Vector2f& Obstacle::getPosition()
{
	return _position;
}

float Obstacle::getRadius()
{
	return _radius;
}

void Obstacle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape);
}