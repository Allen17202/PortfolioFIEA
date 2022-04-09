/*
 * ParticleSwarm.h
 * Author: traqu
 */

#ifndef PARTICLESWARM_H_
#define PARTICLESWARM_H_
#include "Particle.h"

namespace gallen {

class ParticleSwarm {
public:
	const static int NUMPARTICLES = 3000;
private:
	Particle *mem_Particles;
	int lastTimeAccessed;
public:
	ParticleSwarm();
	virtual ~ParticleSwarm();
	void updateParticles(int timeElapsed);
	Particle * const getParticles() {
		return mem_Particles;
	};
};

} /* namespace gallen */

#endif /* PARTICLESWARM_H_ */
