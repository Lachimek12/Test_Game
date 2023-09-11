#pragma once

#include<SDL.h>
#include <iostream>

namespace Data_Loader
{
	//load BMP image and return success status
	bool LoadImage(SDL_Surface** surface, std::string name);
}