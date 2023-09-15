#pragma once

#include <SDL.h>
#include <iostream>

class Animation
{
public:
	Animation();
	~Animation();

	//Deallocate memory
	void Free();

	//Create new animation, width and height are dimensions of 1 animation frame in pixels
	void CreateAnimation(int animationFrames, int width, int height, int sequence[], int sequenceLength);

	//Set number of frames for a single animation state
	void SetAnimationSpeed(int framesPerState);

	//Update frame-based data
	void Update();

	SDL_Rect* GetAnimationClip();

private:
	//Total number of animation frames in a texture
	int animationFrames;

	//how many frames a single animation state lasts
	int framesPerState;

	//frame counter
	int frame;

	//Rects for taking out given frames from a texture
	SDL_Rect* gSpriteClips;

	//array of full order of animation frames untill the restart
	int* sequence;
	int sequenceLength;
};