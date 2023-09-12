#include "Data_Loader.hpp"
#include <iostream>

namespace Data_Loader
{
	SDL_Surface* LoadImage(Window& window, std::string name)
	{
		//The final optimized image
		SDL_Surface* optimizedSurface = NULL;

		//surface where we load image to
		SDL_Surface* surface = NULL;

		//Creating path name
		name = "images/" + name;
		const char* path = name.c_str();

		//Load splash image
		surface = SDL_LoadBMP(path);
		if (surface == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", name.c_str(), SDL_GetError());
		}
		else
		{
			//Convert surface to screen format
			optimizedSurface = SDL_ConvertSurface(surface, window.screenSurface->format, 0);
			if (optimizedSurface == NULL)
			{
				printf("Unable to optimize image %s! SDL Error: %s\n", name.c_str(), SDL_GetError());
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(surface);
		}

		return optimizedSurface;
	}
}