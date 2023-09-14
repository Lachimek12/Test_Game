#include "Data_Loader.hpp"
#include <iostream>

namespace Data_Loader
{
	SDL_Texture* LoadImageAsTexture(Window& window, std::string name)
	{
        //The final texture
        SDL_Texture* newTexture = NULL;

        //Surface for an image
        SDL_Surface* loadedSurface = NULL;

		//Creating path name
		name = "images/" + name;
		const char* path = name.c_str();

        //Load image at specified path
        loadedSurface = SDL_LoadBMP(path);

        if (loadedSurface == NULL)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", name.c_str(), SDL_GetError());
        }
        else
        {
            //Create texture from surface pixels
            newTexture = SDL_CreateTextureFromSurface(window.renderer, loadedSurface);
            if (newTexture == NULL)
            {
                printf("Unable to create texture from %s! SDL Error: %s\n", name.c_str(), SDL_GetError());
            }

            //Get rid of old loaded surface
            SDL_FreeSurface(loadedSurface);
        }

        return newTexture;
	}
}