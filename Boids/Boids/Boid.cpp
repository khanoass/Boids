#include "Boid.h"

Boid::Boid(std::vector<std::shared_ptr<Boid>>& popul, std::vector<std::shared_ptr<Obstacle>>& obst) : 
	_population(popul),
	_obstacles(obst)
{
	_direction = { 0, 0 };
	_position = { 0, 0 };
	_width = 0;
	_length = 0;
	_rotation = 0;
	_speed = 0;
	_separationRadius = 0;
	_cohesionRadius = 0;
	_alignementRadius = 0;
	_alignementWeight = 1;
	_separationWeight = 1;
	_cohesionWeight = 1;

	_showVisionRepresentation = false;
}

void Boid::init()
{
	computeVelocity();

	_triangle.setPrimitiveType(sf::Triangles);
	_triangle.resize(3);

	_triangle[0].color = sf::Color(0, 50, 255, 100);
	_triangle[1].color = sf::Color(0, 50, 255, 100);
	_triangle[2].color = sf::Color(0, 50, 255, 100);

	computeVerticesPosition();

	if (_showVisionRepresentation)
	{
		_alignementRepresentation.setFillColor(sf::Color(255, 0, 0, 20));
		_alignementRepresentation.setOrigin(_alignementRepresentation.getRadius(), _alignementRepresentation.getRadius());
		_alignementRepresentation.setPosition(_position);

		_cohesionRepresentation.setFillColor(sf::Color(0, 255, 0, 20));
		_cohesionRepresentation.setOrigin(_cohesionRepresentation.getRadius(), _cohesionRepresentation.getRadius());
		_cohesionRepresentation.setPosition(_position);

		_separationRepresentation.setFillColor(sf::Color(0, 0, 0, 20));
		_separationRepresentation.setOrigin(_separationRepresentation.getRadius(), _separationRepresentation.getRadius());
		_separationRepresentation.setPosition(_position);

		_linesRepresentation.setPrimitiveType(sf::Lines);
	}
}

void Boid::update()
{
	_position += _direction * _speed;

	if (_showVisionRepresentation)
		_linesRepresentation.clear();

	sf::Vector2f alignement = computeAlignement();
	sf::Vector2f cohesion = computeCohesion();
	sf::Vector2f separation = computeSeparation();

	sf::Vector2f blocking = computeObstacleBlocking();

	_direction += alignement * _alignementWeight;
	_direction += cohesion * _cohesionWeight;
	_direction += separation * _separationWeight;

	_direction += blocking * 100.f;

	rf::VectorMaths::Vector temp = rf::VectorMaths::normalize({ _direction.x, _direction.y });
	_direction = { temp.x, temp.y };

	computeVerticesPosition();

	if (_showVisionRepresentation)
	{
		_alignementRepresentation.setPosition(_position);
		_cohesionRepresentation.setPosition(_position);
		_separationRepresentation.setPosition(_position);
	}

	if (_showVisionRepresentation)
	{
		for (auto& neighbor : _population)
		{
			if (neighbor.get() != this)
			{
				float distance = (neighbor->getPosition().x - _position.x)*(neighbor->getPosition().x - _position.x) + (neighbor->getPosition().y - _position.y)*(neighbor->getPosition().y - _position.y);
				if (distance < _cohesionRadius * _cohesionRadius * 4)
				{
					_linesRepresentation.append({ neighbor->getPosition(), sf::Color::Red });
					_linesRepresentation.append({ _position, sf::Color::Red });
				}
			}
		}
	}
}

void Boid::setGeometry(float width, float length)
{
	_width = width;
	_length = length;
}

void Boid::setRotation(float degree)
{
	_rotation = degree * 3.141592654 / 180;
}

void Boid::setSpeed(float speed)
{
	_speed = speed;
}

void Boid::setPosition(const sf::Vector2f& position)
{
	_position = position;
}

void Boid::setVisionRadiuses(float alignementRadius, float cohesionRadius, float separationRadius)
{
	_alignementRadius = alignementRadius;
	_cohesionRadius = cohesionRadius;
	_separationRadius = separationRadius;

	_alignementRepresentation.setRadius(_alignementRadius);
	_cohesionRepresentation.setRadius(_cohesionRadius);
	_separationRepresentation.setRadius(_separationRadius);

	_alignementRepresentation.setOrigin(_alignementRepresentation.getRadius(), _alignementRepresentation.getRadius());
	_cohesionRepresentation.setOrigin(_cohesionRepresentation.getRadius(), _cohesionRepresentation.getRadius());
	_separationRepresentation.setOrigin(_separationRepresentation.getRadius(), _separationRepresentation.getRadius());
}

void Boid::setBehaviourWeights(float alignementWeight, float cohesionWeight, float separationWeight)
{
	_alignementWeight = alignementWeight;
	_cohesionWeight = cohesionWeight;
	_separationWeight = separationWeight;
}

const sf::Vector2f& Boid::getPosition()
{
	return _position;
}

float Boid::getRotation()
{
	return _rotation;
}

float Boid::getSpeed()
{
	return _speed;
}

const sf::Vector2f& Boid::getVelocity()
{
	return _direction;
}

float Boid::getWidth()
{
	return _width;
}

float Boid::getLength()
{
	return _length;
}

float Boid::getAlignementRadius()
{
	return _alignementRadius;
}

float Boid::getCohesionRadius()
{
	return _cohesionRadius;
}

float Boid::getSeparationRadius()
{
	return _separationRadius;
}

float Boid::getAlignementWeight()
{
	return _alignementWeight;
}

float Boid::getCohesionWeight()
{
	return _cohesionWeight;
}

float Boid::getSeparationWeight()
{
	return _separationWeight;
}

void Boid::setPopulation(const std::vector<std::shared_ptr<Boid>>& population)
{
	_population = population;
}

void Boid::showVisionRepresentation(bool show)
{
	_showVisionRepresentation = show;
}

void Boid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_triangle);
	
	if (_showVisionRepresentation)
	{
		target.draw(_cohesionRepresentation);
		target.draw(_alignementRepresentation);
		target.draw(_separationRepresentation);
		target.draw(_linesRepresentation);
	}
}

void Boid::computeVelocity()
{
	_direction = { std::sin(_rotation), std::cos(_rotation) };
}

sf::Vector2f Boid::computeAlignement()
{
	sf::Vector2f alignementComputation;
	int neighborsCount = 0;

	for (auto& neighbor : _population)
	{
		if (neighbor.get() != this)
		{
			float distance = (neighbor->getPosition().x - _position.x)*(neighbor->getPosition().x - _position.x) + (neighbor->getPosition().y - _position.y)*(neighbor->getPosition().y - _position.y);
			if (distance < _alignementRadius * _alignementRadius * 4)
			{
				alignementComputation += neighbor->getVelocity();
				neighborsCount++;
			}
		}
	}

	if (neighborsCount > 0)
	{
		alignementComputation.x /= neighborsCount;
		alignementComputation.y /= neighborsCount;
		rf::VectorMaths::Vector temp = rf::VectorMaths::normalize({ alignementComputation.x, alignementComputation.y });
		alignementComputation = { temp.x, temp.y };
	}

	return alignementComputation;
}

sf::Vector2f Boid::computeCohesion()
{
	sf::Vector2f cohesionComputation;
	int neighborsCount = 0;

	for (auto& neighbor : _population)
	{
		if (neighbor.get() != this)
		{
			float distance = (neighbor->getPosition().x - _position.x)*(neighbor->getPosition().x - _position.x) + (neighbor->getPosition().y - _position.y)*(neighbor->getPosition().y - _position.y);
			if (distance < _cohesionRadius * _cohesionRadius * 4)
			{
				cohesionComputation += neighbor->getPosition();
				neighborsCount++;
			}
		}
	}

	if (neighborsCount > 0)
	{
		cohesionComputation.x /= neighborsCount;
		cohesionComputation.y /= neighborsCount;
		cohesionComputation = cohesionComputation - _position;
		rf::VectorMaths::Vector temp = rf::VectorMaths::normalize({ cohesionComputation.x, cohesionComputation.y });
		cohesionComputation = { temp.x, temp.y };
	}

	return cohesionComputation;
}

sf::Vector2f Boid::computeSeparation()
{
	sf::Vector2f separationComputation;
	int neighborsCount = 0;

	for (auto& neighbor : _population)
	{
		if (neighbor.get() != this)
		{
			float distance = (neighbor->getPosition().x - _position.x)*(neighbor->getPosition().x - _position.x) + (neighbor->getPosition().y - _position.y)*(neighbor->getPosition().y - _position.y);
			if (distance < _separationRadius * _separationRadius)
			{
				separationComputation += neighbor->getPosition() - _position;
				neighborsCount++;
			}
		}
	}

	if (neighborsCount > 0)
	{
		separationComputation.x /= neighborsCount;
		separationComputation.y /= neighborsCount;
		rf::VectorMaths::Vector temp = rf::VectorMaths::normalize({ separationComputation.x, separationComputation.y });
		separationComputation = { temp.x, temp.y };
		separationComputation *= -1.f;
	}

	return separationComputation;
}

sf::Vector2f Boid::computeObstacleBlocking()
{
	sf::Vector2f blockingComputation;
	int obstacleCount = 0;

	for (auto& obstacle : _obstacles)
	{
		float distance = (obstacle->getPosition().x - _position.x)*(obstacle->getPosition().x - _position.x) + (obstacle->getPosition().y - _position.y)*(obstacle->getPosition().y - _position.y);
		if (distance < (_separationRadius + obstacle->getRadius())*(_separationRadius + obstacle->getRadius()))
		{
			blockingComputation += obstacle->getPosition() - _position;
			obstacleCount++;
		}
	}

	if (obstacleCount > 0)
	{
		blockingComputation.x /= obstacleCount;
		blockingComputation.y /= obstacleCount;
		rf::VectorMaths::Vector temp = rf::VectorMaths::normalize({ blockingComputation.x, blockingComputation.y });
		blockingComputation = { temp.x, temp.y };
		blockingComputation *= -1.f;
	}

	return blockingComputation;
}

void Boid::computeVerticesPosition()
{
	double alpha = std::atan2(_direction.y, _direction.x);
	double beta = 3.141592654 / 2 + alpha;

	sf::Vector2f halfbase = { (float)(_width / 2 * std::cos(beta)), (float)(_width / 2 * std::sin(beta)) };

	_triangle[0].position = _position + sf::Vector2f((float)(_length * std::cos(alpha)), (float)(_length * std::sin(alpha)));
	_triangle[1].position = _position + halfbase;
	_triangle[2].position = _position - halfbase;
}