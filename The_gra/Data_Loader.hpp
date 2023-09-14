#pragma once

#include<SDL.h>
#include <iostream>
#include "Window.hpp"

namespace Data_Loader
{
	//load BMP image and return it
	SDL_Texture* LoadImageAsTexture(Window& window, std::string name);
}