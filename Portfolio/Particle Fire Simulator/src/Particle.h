/*
 * Particle.h
 * Author: traqu
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
namespace gallen {

class Particle {
public:
	// Particles Variable Declaration
	double mem_x;
	double mem_y;
private:
	double mem_speedParticles;
	double mem_directionParticles;
private:
	void initializeParticle();
public:
	Particle();
	virtual ~Particle();
	void updateParticles(int interval);
};

} /* namespace gallen */

#endif /* PARTICLE_H_ */
