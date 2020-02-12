# Boids
A C++ simulation about bird like objects.

## Overview
It is made in C++/SFML 2.5.1.

This is my attempt at implementing "Boids", or flocks of bird-like objects.

## Usage
A boid's direction will depend on three main factors: alignement, cohesion and separation.

Alignement: the boid will try to be aligned on the same angle as its neigbours.
Cohesion: the boid will try to be in the center of mass of its neighbours.
Separation: the boid will try not to bump into its neighbours.

Some sliders are there to adjust these values, as well as their vision radiuses, one for each factor. It is to be noted that their description labels are in french though, sorry about that.

The three first ones are for the vision radiuses of the factors: the larger the radius, the further a boid can see *for this particular factor*.
The three following are for the weights of the factors.
The last slider simply increases the boids' overall speed.

You can add obstacles by left-clicking in the world, and edit them right-clicking on them afterwards. Press Delete to erase an obstacle and the arrow keys to move it while it is being edited. The radius of an obstacle cannot be changed after it has been created though.

## Sidenote
This implementation is totally homemade and some bugs or weird behaviours are to be expected. Anyway, I had a fun time testing with these objects.

Also, all the sources are totally free to use, no need to mention or credit anything *although mentioning the use of the SFML, if used, would be greatly appreciated, as mentioned on their website @ https://www.sfml-dev.org/license.php*. 

Have fun!
