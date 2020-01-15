#pragma once

#include "Entity.h"
#include "rf/VectorMaths.hpp"
#include <iostream>

class Boid : public Entity
{
public:
	Boid(std::vector<std::shared_ptr<Boid>>& popul);

	virtual void init();
	virtual void update();

	void setGeometry(float width, float length);
	void setRotation(float degree);
	void setSpeed(float speed);
	void setPosition(const sf::Vector2f& position);
	void setVisionRadiuses(float alignementRadius, float cohesionRadius, float separationRadius);
	void setBehaviourWeights(float alignementWeight, float cohesionWeight, float separationWeight);

	const sf::Vector2f& getPosition();
	float getRotation();
	float getSpeed();
	const sf::Vector2f& getVelocity();
	float getWidth();
	float getLength();

	float getAlignementRadius();
	float getCohesionRadius();
	float getSeparationRadius();

	float getAlignementWeight();
	float getCohesionWeight();
	float getSeparationWeight();

	void setPopulation(const std::vector<std::shared_ptr<Boid>>& population);

	void showVisionRepresentation(bool show);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float _rotation;
	float _speed;
	sf::Vector2f _direction;
	sf::Vector2f _position;
	float _width;
	float _length;
	float _alignementRadius;
	float _cohesionRadius;
	float _separationRadius;
	float _alignementWeight;
	float _cohesionWeight;
	float _separationWeight;

	std::vector<std::shared_ptr<Boid>>& _population;

	bool _showVisionRepresentation;

	sf::VertexArray _triangle;
	sf::CircleShape _alignementRepresentation, _cohesionRepresentation, _separationRepresentation;
	sf::VertexArray _linesRepresentation;

	void computeVelocity();

	sf::Vector2f computeAlignement();
	sf::Vector2f computeCohesion();
	sf::Vector2f computeSeparation();

	void computeVerticesPosition();
};