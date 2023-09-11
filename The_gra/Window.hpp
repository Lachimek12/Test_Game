#pragma once

#include<SDL.h>

class Window
{
public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screenSurface;

	//Initialization flag
	bool success;

	//Screen dimension constants
	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;

public:
	//initialize sdl with window and screensurface, failure info goes to success flag
	Window();

	//quit sdl
	~Window();

private:

};