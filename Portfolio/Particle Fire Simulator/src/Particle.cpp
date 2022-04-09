/*
 * Particle.cpp
 * Author: traqu
 */

#include "Particle.h"
#include <stdlib.h>
#include <math.h>
namespace gallen {

Particle::Particle() : mem_x(0), mem_y(0) {
	initializeParticle();
}

Particle::~Particle() {
}

// Initializing X and Y Coordinates of each particle to 0
void Particle::initializeParticle() {
	// Setting the direction of the Particle between the range 0 to 360 degrees
	// Setting the travel speed of the particles
	// rand()/RAND_MAX: 0 - 1 range
	// 2*PI*rand()/RAND_MAX: 0 - 6.28 range
	mem_x = 0;
	mem_y = 0;
	mem_directionParticles = (2.0 * M_PI * rand()) / RAND_MAX;
	mem_speedParticles = (0.04 * rand()) / RAND_MAX;
	mem_speedParticles *= mem_speedParticles;
}

void Particle::updateParticles(int interval) {
	mem_directionParticles += interval * -0.00035;

	// Projecting the x and y coordinates into the polar coordinate system
	double speedX = mem_speedParticles * cos(mem_directionParticles);
	double speedY = mem_speedParticles * sin(mem_directionParticles);

	// Updates location of the Particle
	mem_x += speedX * interval;
	mem_y += speedY * interval;

	// Checks for particles going  out of range and populate random postions of particles
	if (mem_x < -1 || mem_x > 1 || mem_y < -1 || mem_y > 1) {
		initializeParticle();
	}

	if(rand() < RAND_MAX / 100) {
		initializeParticle();
	}
}
} /* namespace gallen */
