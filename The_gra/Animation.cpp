#include "Animation.hpp"

Animation::Animation()
{
	animationFrames = 0;
	framesPerState = 0;
	frame = 0;
	sequenceLength = 0;
	gSpriteClips = NULL;
	sequence = NULL;
}

Animation::~Animation()
{
	Free();
}

void Animation::Free()
{
	if (gSpriteClips != NULL)
	{
		delete gSpriteClips;
		gSpriteClips = NULL;
	}

	if (sequence != NULL)
	{
		delete sequence;
		sequence = NULL;
	}

	animationFrames = 0;
	framesPerState = 0;
	frame = 0;
	sequenceLength = 0;
}

void Animation::CreateAnimation(int animationFrames, int width, int height, int sequence[], int sequenceLength)
{
	Free();

	this->animationFrames = animationFrames;
	gSpriteClips = new SDL_Rect[animationFrames];

	//Set sprite clips
	for (int i = 0; i < animationFrames; i++)
	{
		gSpriteClips[i].x = i * width;
		gSpriteClips[i].y = 0;
		gSpriteClips[i].w = width;
		gSpriteClips[i].h = height;
	}

	this->sequence = sequence;
	this->sequenceLength = sequenceLength;
	framesPerState = 4;
}

void Animation::SetAnimationSpeed(int framesPerState)
{
	this->framesPerState = framesPerState;
}

void Animation::Update()
{
	//Go to next frame
	frame++;

	//Cycle animation
	if (frame / framesPerState >= sequenceLength)
	{
		frame = 0;
	}
}

SDL_Rect* Animation::GetAnimationClip()
{
	return &gSpriteClips[sequence[frame / framesPerState]];
}