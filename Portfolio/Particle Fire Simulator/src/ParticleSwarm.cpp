/*
 * ParticleSwarm.cpp
 * Author: traqu
 */

#include "ParticleSwarm.h"

namespace gallen {

// Initializes the Particle Swarm with the number of Particles
ParticleSwarm::ParticleSwarm(): lastTimeAccessed(0) {
	mem_Particles = new Particle[NUMPARTICLES];
}

ParticleSwarm::~ParticleSwarm() {
	delete[] mem_Particles;
}

// update the location of the particles with the time interval based on last accessed time
void ParticleSwarm::updateParticles(int timeElapsed) {
	int interval = timeElapsed - lastTimeAccessed;

	for (int i = 0; i < ParticleSwarm::NUMPARTICLES; i++) {
		mem_Particles[i].updateParticles(interval);
	}

	lastTimeAccessed = timeElapsed;
}

} /* namespace gallen */
