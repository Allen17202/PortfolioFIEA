/*
 * Screen.h
 * Author: traqu
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include <SDL.h>

namespace gallen {

class Screen {
public:
	const static int SCREEN_WIDTH = 900;
	const static int SCREEN_HEIGHT = 700;

private:
	SDL_Window *mem_window;
	SDL_Renderer *mem_render;
	SDL_Texture *mem_texture;
	Uint32 *mem_buf;
	Uint32 *mem_bufBlur;

public:
	Screen();
	bool initialize();
	bool eventProcessor();
	void deallocator();
	void updatingScreen();
	void setPixels(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void blur();
};

} /* namespace gallen */

#endif /* SCREEN_H_ */
