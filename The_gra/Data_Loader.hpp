#pragma once

#include<SDL.h>
#include <iostream>
#include "Window.hpp"

namespace Data_Loader
{
	//load BMP image and return it
	SDL_Surface* LoadImage(Window& window, std::string name);
}