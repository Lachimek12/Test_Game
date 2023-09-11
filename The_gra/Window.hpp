#pragma once

#include<SDL.h>

class Window
{
public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screenSurface;

public:
	Window();
	~Window();

private:

};