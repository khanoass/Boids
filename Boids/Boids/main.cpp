#include "Simulation.h"

int main()
{
	Simulation sim({ 800, 600 }, sf::Style::Titlebar | sf::Style::Close, "Boids", sf::milliseconds(16));
	sim.run();
}