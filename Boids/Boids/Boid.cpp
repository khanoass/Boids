#include "Boid.h"

Boid::Boid()
{
	_velocity = { 0, 0 };
	_position = { 0, 0 };
	_width = 0;
	_length = 0;
	_rotation = 0;
	_speed = 0;
	_visionRadius = 0;

	_showVisionRepresentation = false;
}

void Boid::init()
{
	setVelocity();

	_triangle.setPrimitiveType(sf::Triangles);
	_triangle.resize(3);

	_triangle[0].color = sf::Color::White;
	_triangle[1].color = sf::Color::White;
	_triangle[2].color = sf::Color::White;

	setVerticesPosition();

	if (_showVisionRepresentation)
	{
		_visionRepresentation.setFillColor(sf::Color(0, 100, 255, 10));
		_visionRepresentation.setRadius(_visionRadius);
		_visionRepresentation.setOrigin(_visionRepresentation.getRadius(), _visionRepresentation.getRadius());
		_visionRepresentation.setPosition(_position);
	}
}

void Boid::update()
{
	_position += _velocity;
	setVerticesPosition();

	if (_showVisionRepresentation)
		_visionRepresentation.setPosition(_position);
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

void Boid::setVisionRadius(float visionRadius)
{
	_visionRadius = visionRadius;
}

void Boid::showVisionRepresentation(bool show)
{
	_showVisionRepresentation = show;
}

void Boid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_triangle);
	
	if (_showVisionRepresentation)
		target.draw(_visionRepresentation);
}

void Boid::setVelocity()
{
	sf::Vector2f rotationUnitVec = { std::sin(_rotation), std::cos(_rotation) };
	_velocity = _speed * rotationUnitVec;
}

void Boid::setVerticesPosition()
{
	double alpha = std::atan2(_velocity.y, _velocity.x);
	double beta = 3.141592654 / 2 + alpha;

	sf::Vector2f halfbase = { (float)(_width / 2 * std::cos(beta)), (float)(_width / 2 * std::sin(beta)) };

	_triangle[0].position = _position + sf::Vector2f((float)(_length * std::cos(alpha)), (float)(_length * std::sin(alpha)));
	_triangle[1].position = _position + halfbase;
	_triangle[2].position = _position - halfbase;
}