#include <SDL.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//initialize sdl and create a window
bool init(SDL_Window** window, SDL_Surface** screenSurface);

//load image
bool loadMedia(SDL_Surface** surface);

//destroy window and free images
void close(SDL_Window** window, SDL_Surface** helloWorld);

//Hack to get window to stay up
void stayinAlive();

int main(int argc, char* args[])
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//The image we will load and show on the screen
	SDL_Surface* helloWorld = NULL;

	if (init(&window, &screenSurface))
	{
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 200));

		//Load media
		if (!loadMedia(&helloWorld))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Apply the image
			SDL_BlitSurface(helloWorld, NULL, screenSurface, NULL);
		}

		//Update the surface
		SDL_UpdateWindowSurface(window);

		stayinAlive();
	}
	else
	{
		printf("Failed initialize!\n");
	}

	close(&window, &helloWorld);

	return 0;
}

bool init(SDL_Window** window, SDL_Surface** screenSurface)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		*window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (*window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			*screenSurface = SDL_GetWindowSurface(*window);
		}
	}

	return success;
}

bool loadMedia(SDL_Surface** surface)
{
	//Loading success flag
	bool success = true;

	//Load splash image
	*surface = SDL_LoadBMP("images/helloworld.bmp");
	if (*surface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "images/helloworld.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close(SDL_Window** window, SDL_Surface** helloWorld)
{
	//Deallocate surface
	SDL_FreeSurface(*helloWorld);
	*helloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(*window);
	*window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
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
