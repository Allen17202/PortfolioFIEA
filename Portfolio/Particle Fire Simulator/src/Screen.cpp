/*
 * Screen.cpp
 * Author: traqu
 */

#include "Screen.h"
#include <string.h>
#include <iostream>

namespace gallen {
Screen::Screen() :
		mem_window(NULL), mem_render(NULL), mem_texture(NULL), mem_buf(NULL), mem_bufBlur(NULL) {
}

bool Screen::initialize() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	// Create a Window in the middle of the screen
	mem_window = SDL_CreateWindow("Particle Swarm Explosion!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	// Variable Creation Check
	if (mem_window == NULL) {
		SDL_Quit();
		return false;
	}

	// Creation and Variable Check for renderer and texture for the window
	mem_render = SDL_CreateRenderer(mem_window, -1, SDL_RENDERER_PRESENTVSYNC);
	mem_texture = SDL_CreateTexture(mem_render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Render Check
	if (mem_render == NULL) {
		SDL_DestroyWindow(mem_window);
		SDL_Quit();
		return false;
	}

	// Texture Check
	if (mem_texture == NULL) {
		SDL_DestroyRenderer(mem_render);
		SDL_DestroyWindow(mem_window);
		SDL_Quit();
		return false;
	}

	// Initializes buffers and sets up display
	mem_buf = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	mem_bufBlur = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	memset(mem_buf, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(mem_bufBlur, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	return true;
}

bool Screen::eventProcessor() {
	SDL_Event event;
	// Waits for user to quit by pressing X in the upper right hand side
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

// Cleanup and Quit
void Screen::deallocator() {
	delete[] mem_buf;
	delete[] mem_bufBlur;
	SDL_DestroyRenderer(mem_render);
	SDL_DestroyTexture(mem_texture);
	SDL_DestroyWindow(mem_window);
	SDL_Quit();
}

void Screen::updatingScreen() {
	SDL_UpdateTexture(mem_texture, NULL, mem_buf, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(mem_render);
	SDL_RenderCopy(mem_render, mem_texture, NULL, NULL);
	SDL_RenderPresent(mem_render);
}

void Screen::setPixels(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	Uint32 colors = 0;

	if (x >= Screen::SCREEN_WIDTH || x < 0 || y >= Screen::SCREEN_HEIGHT || y < 0) {
		return;
	}
	colors += red;
	colors <<= 8;
	colors += green;
	colors <<= 8;
	colors += blue;
	colors <<= 8;
	colors += 0xFF;
	mem_buf[(y * SCREEN_WIDTH) + x] = colors;
}

void Screen::blur() {
	// Swapping buffers, pixels in bufBlur and drawing to buf
	Uint32 *tempBuf = mem_buf;
	mem_buf = mem_bufBlur;
	mem_bufBlur = tempBuf;

	// Box Blur
	// 0 0 0
	// 0 1 0
	// 0 0 0

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			int redSum = 0;
			int greenSum = 0;
			int blueSum = 0;
			for (int col = -1; col <= 1; col++) {
				for (int row = -1; row <= 1; row++) {
					int curX = x + col;
					int curY = y + row;
					if (curX >= 0 && curX < SCREEN_WIDTH && curY >= 0 && curY < SCREEN_HEIGHT) {
						Uint32 color = mem_bufBlur[curY * SCREEN_WIDTH + curX];
						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;
						redSum += red;
						greenSum += green;
						blueSum += blue;
					}
				}
			}
			Uint8 red = redSum / 9;
			Uint8 green = greenSum / 9;
			Uint8 blue = blueSum / 9;
			setPixels(x, y, red, green, blue);
		}
	}
}

} /* namespace gallen */
