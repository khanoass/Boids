#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
public:
	Entity();

	void init();
	void update();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};