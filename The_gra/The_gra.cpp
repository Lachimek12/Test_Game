#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Window.hpp"
#include "Data_Loader.hpp"
#include "LTexture.hpp"


const int WALKING_ANIMATION_FRAMES = 11;

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
void close(LTexture& gFooTexture, LTexture& gBackgroundTexture);

//Hack to get window to stay up
void stayinAlive(Window& window, LTexture& gFooTexture, LTexture& gBackgroundTexture, SDL_Rect gSpriteClips[], int sequence[]);


int main(int argc, char* args[])
{
	//Object handling window and main screen surface
	Window window;

	//Scene textures
	LTexture gFooTexture;
	LTexture gBackgroundTexture;

	//Walking animation
	SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];

	int sequence[22] = { 3,4,5,6,7,8,7,6,9,10,9,6,5,4,5,6,5,4,5,6,5,4 };

	if (window.success)
	{
		//Load media //DANCE.BMP POWIÊKSZYÆ TUTAJ W KLASIE LTEXTURE X2
		if (gFooTexture.LoadFromFile(window, "dance.bmp") && gBackgroundTexture.LoadFromFile(window, "background.bmp"))
		{
			//Set sprite clips
			for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++)
			{
				gSpriteClips[i].x = i * 100;
				gSpriteClips[i].y = 0;
				gSpriteClips[i].w = 100;
				gSpriteClips[i].h = 80;
			}

			stayinAlive(window, gFooTexture, gBackgroundTexture, gSpriteClips, sequence);
		}
	}

	close(gFooTexture, gBackgroundTexture);

	return 0;
}

void close(LTexture& gFooTexture, LTexture& gBackgroundTexture)
{
	//Free loaded images
	gFooTexture.Free();
	gBackgroundTexture.Free();
}

void stayinAlive(Window& window, LTexture& gFooTexture, LTexture& gBackgroundTexture, SDL_Rect gSpriteClips[], int sequence[])
{
	SDL_Event e;

	//Main loop flag
	bool quit = false;

	//Current animation frame
	int frame = 0;

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
		SDL_Rect* currentClip = &gSpriteClips[sequence[frame / 12]];
		gFooTexture.Render(window, 0, 0);

		//Update screen
		SDL_RenderPresent(window.renderer);

		//Go to next frame
		frame++;

		//Cycle animation
		if (frame / 12 >= 22)
		{
			frame = 0;
		}
	}
}
