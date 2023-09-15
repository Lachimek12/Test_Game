#pragma once

#include <SDL.h>
#include<iostream>
#include "Window.hpp"
#include "Animation.hpp"

//Texture wrapper class
class LTexture
{
public:
    //Animation handler
    Animation* animation;


    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool LoadFromFile(Window& window, std::string path, bool isAnimated = false);

    //Deallocates texture
    void Free();

    //Renders texture at given point
    void Render(Window& window, int x, int y);

    //Gets image dimensions
    int GetWidth();
    int GetHeight();

    //Change resize parameters
    void SetResizeWidth(int resizeWidth);
    void SetResizeHeight(int resizeHeight);

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;

    //resize image multiplier
    int resizeWidth;
    int resizeHeight;
};