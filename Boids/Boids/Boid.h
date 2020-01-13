#pragma once

#include "Entity.h"
#include <iostream>

class Boid : public Entity
{
public:
	Boid();

	virtual void init();
	virtual void update();

	void setGeometry(float width, float length);
	void setRotation(float degree);
	void setSpeed(float speed);
	void setPosition(const sf::Vector2f& position);
	void setVisionRadius(float visionRadius);

	void showVisionRepresentation(bool show);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float _rotation;
	float _speed;
	sf::Vector2f _velocity;
	sf::Vector2f _position;
	float _width;
	float _length;
	float _visionRadius;

	bool _showVisionRepresentation;

	sf::VertexArray _triangle;
	sf::CircleShape _visionRepresentation;

	void setVelocity();

	void setVerticesPosition();
};