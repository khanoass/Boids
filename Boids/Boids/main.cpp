#include "Simulation.h"

int main()
{
	sf::Font opensans;
	opensans.loadFromFile("opensans.ttf");

	Simulation sim({ 1920, 1080 }, sf::Style::Fullscreen, "Boids", sf::milliseconds(16), opensans);
	sim.run();
}