#include <SDL.h>
#include <iostream>
#include "Window.hpp"
#include "Data_Loader.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


//destroy window and free images
void close(SDL_Surface** helloWorld);

//Hack to get window to stay up
void stayinAlive();


int main(int argc, char* args[])
{
	//Object handling window and main screen surface
	Window window;

	//The image we will load and show on the screen
	SDL_Surface* helloWorld = NULL;

	if (window.success)
	{
		SDL_FillRect(window.screenSurface, NULL, SDL_MapRGB(window.screenSurface->format, 0, 0, 200));

		//Load media
		if (!Data_Loader::LoadImage(&helloWorld, "helloworld.bmp"))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Apply the image
			SDL_BlitSurface(helloWorld, NULL, window.screenSurface, NULL);
		}

		//Update the surface
		SDL_UpdateWindowSurface(window.window);

		stayinAlive();
	}
	else
	{
		printf("Failed initialize!\n");
	}

	close(&helloWorld);

	return 0;
}

void close(SDL_Surface** helloWorld)
{
	//Deallocate surface
	SDL_FreeSurface(*helloWorld);
	*helloWorld = NULL;
}

void stayinAlive()
{
	SDL_Event e;
	bool quit = false;

	while (quit == false)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
}
