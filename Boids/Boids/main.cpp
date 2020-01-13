#include "Simulation.h"

int main()
{
	Simulation sim({ 1200, 800 }, sf::Style::Titlebar | sf::Style::Close, "Boids", sf::milliseconds(16));
	sim.run();
}