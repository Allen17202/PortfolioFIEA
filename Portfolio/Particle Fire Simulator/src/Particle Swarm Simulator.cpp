//============================================================================
// Name        : Particle.cpp
// Author      : Gregory Allen
//============================================================================

#include <iostream>
#include <SDL.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Screen.h"
#include "ParticleSwarm.h"

using namespace std;
using namespace gallen;

int main(int argc, char *argv[]) {
	Screen display;
	srand(time(NULL));

	if (display.initialize() == false) {
		cout << "SDL Error Initializing" << endl;
	}

	ParticleSwarm swarm;
	int halfWidth = Screen::SCREEN_WIDTH / 2;
	int halfHeight = Screen::SCREEN_HEIGHT / 2;
	bool altColor = true;
	while (true) {
		// Update Particles

		// Draw Particles
		int timeElapsed = SDL_GetTicks();
		swarm.updateParticles(timeElapsed);

		// could also be sin function
		// can play with values here to change colors
		unsigned char redColorChange = (unsigned char) ((1 + sin(timeElapsed * 0.0005)) * 128);
		unsigned char greenColorChange = (unsigned char) ((1 + cos(timeElapsed * 0.0008)) * 128);
		unsigned char blueColorChange = (unsigned char) ((1 + sin(timeElapsed * 0.0004)) * 128);

		const Particle *const selectParticles = swarm.getParticles();
		for (int i = 0; i < ParticleSwarm::NUMPARTICLES; i++) {
			Particle p = selectParticles[i];
			int x = (p.mem_x + 1) * halfWidth;
			int y = p.mem_y * halfWidth + halfHeight;
			if(altColor) {
				display.setPixels(x, y, redColorChange, greenColorChange, blueColorChange);
				altColor = false;
			}
			else {
				//display.setPixels(x, y, greenColorChange, redColorChange, blueColorChange);
				//display.setPixels(x, y, redColorChange, redColorChange, blueColorChange);
				display.setPixels(x, y, greenColorChange, greenColorChange, blueColorChange);

				altColor = true;
			}
		}
		// Blur the particles
		display.blur();

		// Draw Screen
		display.updatingScreen();

		// Check for messages/events
		if (display.eventProcessor() == false) {
			break;
		}
	}

	display.deallocator();
	return 0;
}
