#include "Data_Loader.hpp"
#include <iostream>

namespace Data_Loader
{
	bool LoadImage(SDL_Surface** surface, std::string name)
	{
		//Loading success flag
		bool success = true;

		//Creating path name
		name = "images/" + name;
		const char* path = name.c_str();

		//Load splash image
		*surface = SDL_LoadBMP(path);
		if (*surface == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", name.c_str(), SDL_GetError());
			success = false;
		}

		return success;
	}
}