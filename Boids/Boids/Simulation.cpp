#include "Simulation.h"

Simulation::Simulation(const sf::Vector2u& windowSize, const sf::Uint32& windowStyle, const std::string& windowTitle, const sf::Time& updateTime, const sf::Font& font) :
	_windowSize(windowSize),
	_windowStyle(windowStyle),
	_windowTitle(windowTitle),
	_updateTime(updateTime),
	_sliderAlignementRadius({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING }, font, 0, 300, FLT_SLIDERS_LENGTH, "", UINT_SLIDER_DECIMALS_COUNT),
	_sliderCohesionRadius({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*2 }, font, 0, 300, FLT_SLIDERS_LENGTH, "", UINT_SLIDER_DECIMALS_COUNT),
	_sliderSeparationRadius({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*3 }, font, 0, 300, FLT_SLIDERS_LENGTH, "", UINT_SLIDER_DECIMALS_COUNT),
	_sliderAlignementWeight({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*4 }, font, 0, 20, FLT_SLIDERS_LENGTH, "", UINT_SLIDER_DECIMALS_COUNT),
	_sliderCohesionWeight({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*5 }, font, 0, 20, FLT_SLIDERS_LENGTH, "", UINT_SLIDER_DECIMALS_COUNT),
	_sliderSeparationWeight({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*6 }, font, 0, 20, FLT_SLIDERS_LENGTH, "", UINT_SLIDER_DECIMALS_COUNT),
	_sliderBoidSpeed({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*7 }, font, 0, 10, FLT_SLIDERS_LENGTH, "", UINT_SLIDER_DECIMALS_COUNT),
	_textAlignementRadius("Rayon de vision : alignement [px]", font, UINT_TEXT_CHARACTER_SIZE),
	_textCohesionRadius("Rayon de vision : cohesion [px]", font, UINT_TEXT_CHARACTER_SIZE),
	_textSeparationRadius("Rayon de vision : séparation [px]", font, UINT_TEXT_CHARACTER_SIZE),
	_textAlignementWeight("Poids de la propriété : alignement [ratio]", font, UINT_TEXT_CHARACTER_SIZE),
	_textCohesionWeight("Poids de la propriété : cohesion [ratio]", font, UINT_TEXT_CHARACTER_SIZE),
	_textSeparationWeight("Poids de la propriété : séparation [ratio]", font, UINT_TEXT_CHARACTER_SIZE),
	_textBoidSpeed("Vitesse d'un boid [px/frame]", font, UINT_TEXT_CHARACTER_SIZE)
{
	_textAlignementRadius.setPosition({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING+ FLT_SLIDER_TEXT_OFFSET });
	_textCohesionRadius.setPosition({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*2 + FLT_SLIDER_TEXT_OFFSET });
	_textSeparationRadius.setPosition({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*3 + FLT_SLIDER_TEXT_OFFSET });
	_textAlignementWeight.setPosition({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*4 + FLT_SLIDER_TEXT_OFFSET });
	_textCohesionWeight.setPosition({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*5 + FLT_SLIDER_TEXT_OFFSET });
	_textSeparationWeight.setPosition({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*6 + FLT_SLIDER_TEXT_OFFSET });
	_textBoidSpeed.setPosition({ (float)_windowSize.x - FLT_WIDGETS_RIGHT, FLT_SLIDERS_SPACING*7 + FLT_SLIDER_TEXT_OFFSET });
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

			_win.clear(sf::Color(60, 60, 60));
			render();
			_win.display();
		}
	}
}

void Simulation::init()
{
	_world.create({ _windowSize.x - 540, _windowSize.y - 40 }, { 20, 20 }, World::Type::Mirrored);

	_sliderAlignementRadius.SetValue(80.f);
	_sliderCohesionRadius.SetValue(100.f);
	_sliderSeparationRadius.SetValue(10.f);
	_sliderAlignementWeight.SetValue(10);
	_sliderCohesionWeight.SetValue(1);
	_sliderSeparationWeight.SetValue(10);

	_sliderBoidSpeed.SetValue(4);

	for (size_t i = 0; i < 500; i++)
	{
		std::shared_ptr<Boid> boid = std::make_shared<Boid>(_population, _obstacles);

		boid->setGeometry(5, 10);
		boid->setRotation(rf::Random::getAngle());
		boid->setSpeed(_sliderBoidSpeed.GetValue());
		sf::Vector2f randomPosition = { rf::Random::getFloat((float)_world.getOffset().x, (float)_world.getOffset().x + (float)_world.getSize().x), rf::Random::getFloat((float)_world.getOffset().y, (float)_world.getOffset().y + (float)_world.getSize().y) };
		boid->setPosition(randomPosition);
		boid->setVisionRadiuses(_sliderAlignementRadius.GetValue(), _sliderCohesionRadius.GetValue(), _sliderSeparationRadius.GetValue());
		boid->setBehaviourWeights(_sliderAlignementWeight.GetValue(), _sliderCohesionWeight.GetValue(), _sliderSeparationWeight.GetValue());
		boid->showVisionRepresentation(false);

		_population.push_back(boid);
		_world.addBoid(boid);
	}

	_world.init();
}

void Simulation::update()
{
	if (_sliderAlignementRadius.ValueChanged(_win, _event))
	{
		for (auto& boid : _population)
			boid->setVisionRadiuses(_sliderAlignementRadius.GetValue(), boid->getCohesionRadius(), boid->getSeparationRadius());
	}

	if (_sliderCohesionRadius.ValueChanged(_win, _event))
	{
		for (auto& boid : _population)
			boid->setVisionRadiuses(boid->getCohesionRadius(), _sliderCohesionRadius.GetValue(), boid->getSeparationRadius());
	}

	if (_sliderSeparationRadius.ValueChanged(_win, _event))
	{
		for (auto& boid : _population)
			boid->setVisionRadiuses(boid->getAlignementRadius(), boid->getCohesionRadius(), _sliderSeparationRadius.GetValue());
	}

	if (_sliderAlignementWeight.ValueChanged(_win, _event))
	{
		for (auto& boid : _population)
			boid->setBehaviourWeights(_sliderAlignementWeight.GetValue(), boid->getCohesionWeight(), boid->getSeparationWeight());
	}

	if (_sliderCohesionWeight.ValueChanged(_win, _event))
	{
		for (auto& boid : _population)
			boid->setBehaviourWeights(boid->getAlignementWeight(), _sliderCohesionWeight.GetValue(), boid->getSeparationWeight());
	}

	if (_sliderSeparationWeight.ValueChanged(_win, _event))
	{
		for (auto& boid : _population)
			boid->setBehaviourWeights(boid->getAlignementWeight(), boid->getCohesionWeight(), _sliderSeparationWeight.GetValue());
	}

	if (_sliderBoidSpeed.ValueChanged(_win, _event))
	{
		for (auto& boid : _population)
			boid->setSpeed(_sliderBoidSpeed.GetValue());
	}

	if (_inserting)
	{
		_currentObstacle = std::make_shared<Obstacle>();
		sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(_win));
		float radius = std::sqrt((pos.x - _initialPosition.x)*(pos.x - _initialPosition.x) + (pos.y - _initialPosition.y)*(pos.y - _initialPosition.y));
		_currentObstacle->setRadius(radius / 2);
		_currentObstacle->setPosition(pos);
		_currentObstacle->setColor(sf::Color::Red);
		_currentObstacle->init();
	}

	_world.update();
}

void Simulation::updateEvents()
{
	switch (_event.type)
	{
	case sf::Event::Closed:
		_win.close();
		break;
	case sf::Event::KeyReleased:
		if (_event.key.code == sf::Keyboard::Escape)
			_win.close();
		break;
	case sf::Event::MouseButtonPressed:
		if (_event.mouseButton.button == sf::Mouse::Left)
		{
			if (_inserting)
			{
				_inserting = false;
				_currentObstacle->setColor(sf::Color::Black);
				_currentObstacle->init();
				_obstacles.push_back(_currentObstacle);
				_world.addEntity(_currentObstacle);
			}
			else
			{
				sf::Vector2i pos = sf::Mouse::getPosition(_win);
				_inserting = pos.x > _world.getOffset().x && pos.x < _world.getOffset().x + _world.getSize().x && pos.y > _world.getOffset().y && pos.y < _world.getOffset().y + _world.getSize().y;
				if (_inserting)
					_initialPosition = sf::Vector2f(pos);
			}
		}
		else if (_event.mouseButton.button == sf::Mouse::Right)
		{
			if (_inserting)
				_inserting = false;
		}
		break;
	}
}

void Simulation::render()
{
	_win.draw(_world);

	if (_inserting)
		_win.draw(*_currentObstacle);

	_win.draw(_sliderAlignementRadius);
	_win.draw(_sliderCohesionRadius);
	_win.draw(_sliderSeparationRadius);
	_win.draw(_sliderAlignementWeight);
	_win.draw(_sliderCohesionWeight);
	_win.draw(_sliderSeparationWeight);
	_win.draw(_sliderBoidSpeed);

	_win.draw(_textAlignementRadius);
	_win.draw(_textCohesionRadius);
	_win.draw(_textSeparationRadius);
	_win.draw(_textAlignementWeight);
	_win.draw(_textCohesionWeight);
	_win.draw(_textSeparationWeight);
	_win.draw(_textBoidSpeed);
}