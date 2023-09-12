#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Window.hpp"
#include "Data_Loader.hpp"

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
	KEY_PRESS_SURFACE_SPACE_BAR
};

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
		helloWorld = Data_Loader::LoadImage(window, "helloworld.bmp");
		if (helloWorld != NULL)
		{
			//Apply the image stretched
			SDL_Rect stretchRect;
			stretchRect.x = 0;
			stretchRect.y = 0;
			stretchRect.w = Window::SCREEN_WIDTH;
			stretchRect.h = Window::SCREEN_HEIGHT;
			SDL_BlitScaled(helloWorld, NULL, window.screenSurface, &stretchRect);

			//Apply the image
			SDL_BlitSurface(helloWorld, NULL, window.screenSurface, NULL);
		}

		//Update the surface
		SDL_UpdateWindowSurface(window.window);

		stayinAlive();
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
			//User presses a key
			else if (e.type == SDL_KEYDOWN)
			{
				//Select surfaces based on key press
				switch (e.key.keysym.sym)
				{
				case SDLK_SPACE:
					quit = true;
					break;
				}
			}
		}
	}
}
