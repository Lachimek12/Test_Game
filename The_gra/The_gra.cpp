#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Window.hpp"
#include "Data_Loader.hpp"
#include "LTexture.hpp"


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
void close(LTexture& gFooTexture);

//Hack to get window to stay up
void stayinAlive(Window& window, LTexture& gFooTexture);


int main(int argc, char* args[])
{
	//Object handling window and main screen surface
	Window window;

	//Scene textures
	LTexture gFooTexture;

	if (window.success)
	{
		//Load media
		if (gFooTexture.LoadFromFile(window, "dance.bmp", true))
		{
			int* sequence = { new int[22] { 3,4,5,6,7,8,7,6,9,10,9,6,5,4,5,6,5,4,5,6,5,4 } };
			gFooTexture.animation->CreateAnimation(11, 100, 80, sequence, 22);
			gFooTexture.SetResizeHeight(2);
			gFooTexture.SetResizeWidth(2);
			gFooTexture.animation->SetAnimationSpeed(12);
			sequence = NULL;

			stayinAlive(window, gFooTexture);
		}
	}

	//close(gFooTexture);

	return 0;
}

void close(LTexture& gFooTexture)
{
	//Free loaded images
	gFooTexture.Free();
}

void stayinAlive(Window& window, LTexture& gFooTexture)
{
	SDL_Event e;

	//Main loop flag
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

		//Clear screen
		SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(window.renderer);

		//Render background texture to screen
		//gBackgroundTexture.Render(window, 0, 0);

		//Render current frame
		gFooTexture.Render(window, 0, 0);

		//Update screen
		SDL_RenderPresent(window.renderer);

		gFooTexture.animation->Update();
	}
}
