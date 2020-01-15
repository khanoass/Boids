#pragma once

#include "World.h"
#include "Boid.h"
#include "rf/Random.hpp"

class Simulation
{
public:
	Simulation(const sf::Vector2u& windowSize, const sf::Uint32& windowStyle, const std::string& windowTitle, const sf::Time& updateTime);

	void run();

private:
	sf::Vector2u _windowSize;
	sf::Uint32 _windowStyle;
	std::string _windowTitle;
	sf::Time _updateTime;

	sf::RenderWindow _win;
	sf::Event _event;
	sf::Clock _updateClock;

	World _world;

	void init();
	void update();
	void updateEvents();
	void render();
};