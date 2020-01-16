#include "Simulation.h"

int main(int argc, const char** argv)
{
	sf::Font opensans;
	opensans.loadFromFile("opensans.ttf");

	Simulation *sim = new Simulation({ 1800, 900 }, sf::Style::Close | sf::Style::Titlebar, "Boids", sf::milliseconds(16), opensans);
	sim->run();
	delete sim;

	return EXIT_SUCCESS;
}