#pragma once

#include<SDL.h>

class Window
{
public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The window renderer
	SDL_Renderer* renderer;

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