#pragma once

#include "World.h"
#include "Boid.h"
#include "rf/Random.hpp"
#include "slider/WidgetSlider.h"

class Simulation
{
public:
	Simulation(const sf::Vector2u& windowSize, const sf::Uint32& windowStyle, const std::string& windowTitle, const sf::Time& updateTime, const sf::Font& font);

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

	std::vector<std::shared_ptr<Boid>> _population;

	WidgetSlider _sliderAlignementRadius;
	WidgetSlider _sliderCohesionRadius;
	WidgetSlider _sliderSeparationRadius;

	WidgetSlider _sliderAlignementWeight;
	WidgetSlider _sliderCohesionWeight;
	WidgetSlider _sliderSeparationWeight;

	WidgetSlider _sliderBoidSpeed;

	sf::Text _textAlignementRadius;
	sf::Text _textCohesionRadius;
	sf::Text _textSeparationRadius;

	sf::Text _textAlignementWeight;
	sf::Text _textCohesionWeight;
	sf::Text _textSeparationWeight;

	sf::Text _textBoidSpeed;

	void init();
	void update();
	void updateEvents();
	void render();
};