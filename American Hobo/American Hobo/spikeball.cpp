#include "spikeball.h"

//=============================================================================
// default constructor
//=============================================================================
Spikeball::Spikeball() : Entity()
{
	active = false;
	visible = false; 
	spriteData.width = spikeballNS::WIDTH;
	spriteData.height = spikeballNS::HEIGHT;
	spriteData.rect.bottom = spikeballNS::HEIGHT;
	spriteData.rect.right = spikeballNS::WIDTH;
	cols = spikeballNS::TEXTURE_COLS;
	frameDelay = spikeballNS::ANIMATION_DELAY;
	startFrame = 0;       
	endFrame = 0;       
	currentFrame = startFrame;
	

}

//=============================================================================
// update
// typically called once per frame
//=============================================================================
void Spikeball::update(Entity *hero, float frameTime)
{
	//...
	
	Entity::update(frameTime);
}