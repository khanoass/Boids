#include "Simulation.h"

Simulation::Simulation(const sf::Vector2u& windowSize, const sf::Uint32& windowStyle, const std::string& windowTitle, const sf::Time& updateTime, const sf::Font& font) :
	_windowSize(windowSize),
	_windowStyle(windowStyle),
	_windowTitle(windowTitle),
	_updateTime(updateTime),
	_sliderAlignementRadius({ (float)_windowSize.x - 460, 100 }, font, 0, 300, 300, "", 2),
	_sliderCohesionRadius({ (float)_windowSize.x - 460, 200 }, font, 0, 300, 300, "", 2),
	_sliderSeparationRadius({ (float)_windowSize.x - 460, 300 }, font, 0, 300, 300, "", 2),
	_sliderAlignementWeight({ (float)_windowSize.x - 460, 400 }, font, 0, 20, 300, "", 2),
	_sliderCohesionWeight({ (float)_windowSize.x - 460, 500 }, font, 0, 20, 300, "", 2),
	_sliderSeparationWeight({ (float)_windowSize.x - 460, 600 }, font, 0, 20, 300, "", 2),
	_sliderBoidSpeed({ (float)_windowSize.x - 460, 700 }, font, 0, 10, 300, "", 2),
	_textAlignementRadius("Rayon de vision : alignement [px]", font, 15),
	_textCohesionRadius("Rayon de vision : cohesion [px]", font, 15),
	_textSeparationRadius("Rayon de vision : séparation [px]", font, 15),
	_textAlignementWeight("Poids de la propriété : alignement [ratio]", font, 15),
	_textCohesionWeight("Poids de la propriété : cohesion [ratio]", font, 15),
	_textSeparationWeight("Poids de la propriété : séparation [ratio]", font, 15),
	_textBoidSpeed("Vitesse d'un boid [px/frame]", font, 15)
{
	_textAlignementRadius.setPosition({ (float)_windowSize.x - 460, 60 });
	_textCohesionRadius.setPosition({ (float)_windowSize.x - 460, 160 });
	_textSeparationRadius.setPosition({ (float)_windowSize.x - 460, 260 });
	_textAlignementWeight.setPosition({ (float)_windowSize.x - 460, 360 });
	_textCohesionWeight.setPosition({ (float)_windowSize.x - 460, 460 });
	_textSeparationWeight.setPosition({ (float)_windowSize.x - 460, 560 });
	_textBoidSpeed.setPosition({ (float)_windowSize.x - 460, 660 });
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
	_world.create({ _windowSize.x - 540, _windowSize.y - 40 }, { 20, 20 }, World::Type::Mirrored);

	_sliderAlignementRadius.SetValue(80.f);
	_sliderCohesionRadius.SetValue(100.f);
	_sliderSeparationRadius.SetValue(10.f);

	_sliderAlignementWeight.SetValue(10);
	_sliderCohesionWeight.SetValue(1);
	_sliderSeparationWeight.SetValue(10);

	_sliderBoidSpeed.SetValue(4);

	for (size_t i = 0; i < 1000; i++)
	{
		std::shared_ptr<Boid> boid = std::make_shared<Boid>(_population);

		boid->setGeometry(5, 10);
		boid->setRotation(rf::Random::getAngle());
		boid->setSpeed(_sliderBoidSpeed.GetValue());
		sf::Vector2f randomPosition = { rf::Random::getFloat((float)_world.getOffset().x, (float)_world.getOffset().x + (float)_world.getSize().x), rf::Random::getFloat((float)_world.getOffset().y, (float)_world.getOffset().y + (float)_world.getSize().y) };
		boid->setPosition(randomPosition);
		boid->setVisionRadiuses(_sliderAlignementRadius.GetValue(), _sliderCohesionRadius.GetValue(), _sliderSeparationRadius.GetValue());
		boid->setBehaviourWeights(_sliderAlignementWeight.GetValue(), _sliderCohesionWeight.GetValue(), _sliderSeparationWeight.GetValue());
		boid->showVisionRepresentation(false);

		_world.addBoid(boid);
	}

	_world.init();
	_population = _world.getBoids();
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
	}
}

void Simulation::render()
{
	_win.draw(_world);

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