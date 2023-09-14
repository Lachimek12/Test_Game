#include "LTexture.hpp"

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    resizeHeight = 1;
    resizeWidth = 1;
    animation = NULL;
}

LTexture::~LTexture()
{
    //Deallocate
    Free();
}

bool LTexture::LoadFromFile(Window& window, std::string name, bool isAnimated)
{
    //Get rid of preexisting texture
    Free();

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
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xF2, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(window.renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", name.c_str(), SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    if (isAnimated)
    {
        animation = new Animation;
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::Free()
{
    //Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        resizeHeight = 1;
        resizeWidth = 1;
    }

    if (animation != NULL)
    {
        delete animation;
        animation = NULL;
    }
}

void LTexture::Render(Window& window, int x, int y)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth * resizeWidth, mHeight * resizeHeight };
    SDL_Rect* clip = NULL;

    if (animation != NULL)
    {
        clip = animation->GetAnimationClip();
    }

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w * resizeWidth;
        renderQuad.h = clip->h * resizeHeight;
    }

    SDL_RenderCopy(window.renderer, mTexture, clip, &renderQuad);
}

int LTexture::GetWidth()
{
    return mWidth;
}

int LTexture::GetHeight()
{
    return mHeight;
}

void LTexture::SetResizeWidth(int resizeWidth)
{
    if (resizeWidth > 0 && resizeWidth < 1000000)
    {
        this->resizeWidth = resizeWidth;
    }
}

void LTexture::SetResizeHeight(int resizeHeight)
{
    if (resizeHeight > 0 && resizeHeight < 1000000)
    {
        this->resizeHeight = resizeHeight;
    }
}