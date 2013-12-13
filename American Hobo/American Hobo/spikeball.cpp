#include "spikeball.h"


Spikeball::Spikeball() : Entity()
{
	active = false;
	visible = false; 
	spriteData.width = spikeballNS::WIDTH;
	spriteData.height = spikeballNS::HEIGHT;
	spriteData.rect.top = 0;//spikeballNS::OFFSET;
	spriteData.rect.bottom = 100;//spikeballNS::HEIGHT + spikeballNS::OFFSET;
	spriteData.rect.left = spikeballNS::OFFSET;
	spriteData.rect.right = spikeballNS::WIDTH + spikeballNS::OFFSET;
	cols = spikeballNS::TEXTURE_COLS;
	frameDelay = spikeballNS::ANIMATION_DELAY;
	startFrame = 0;       
	endFrame = 0;       
	currentFrame = startFrame;
}
//
//void Spikeball::update(Entity *hero, float frameTime)
//{
//	//...
//	
//	Entity::update(frameTime);
//}