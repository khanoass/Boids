#include "Simulation.h"

Simulation::Simulation(const sf::Vector2u& windowSize, const sf::Uint32& windowStyle, const std::string& windowTitle, const sf::Time& updateTime) :
	_windowSize(windowSize),
	_windowStyle(windowStyle),
	_windowTitle(windowTitle),
	_updateTime(updateTime)
{
}

void Simulation::run()
{
	_win.create(sf::VideoMode(_windowSize.x, _windowSize.y), _windowTitle, _windowStyle);
	init();

	while (_win.isOpen())
	{
		while (_win.pollEvent(_event))
			updateEvents();

		if (_updateClock.getElapsedTime() > _updateTime)
		{
			_updateClock.restart();
			update();

			_win.clear();
			render();
			_win.display();
		}
	}
}

void Simulation::init()
{
	for (size_t i = 0; i < 30; i++)
	{
		std::shared_ptr<Boid> boid = std::make_shared<Boid>();

		boid->setGeometry(15, 30);
		boid->setRotation(Random::nextFloat(0, 360));
		boid->setSpeed(1);
		boid->setPosition({ 600, 400 });
		boid->setVisionRadius(80);
		boid->showVisionRepresentation(true);

		_world.addEntity(boid);
	}

	_world.init();
}

void Simulation::update()
{
	_world.update();
}

void Simulation::updateEvents()
{
	switch (_event.type)
	{
	case sf::Event::Closed:
		_win.close();
		break;
	}
}

void Simulation::render()
{
	_win.draw(_world);
}