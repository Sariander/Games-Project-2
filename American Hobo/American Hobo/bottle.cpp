#include "bottle.h"

//=============================================================================
// default constructor
//=============================================================================
Bottle::Bottle() : Entity()
{
	active = false;                                 // torpedo starts inactive
	spriteData.width = bottleNS::WIDTH;     // size of 1 image
	spriteData.height = bottleNS::HEIGHT;
	spriteData.rect.bottom = bottleNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bottleNS::WIDTH;
	cols = bottleNS::TEXTURE_COLS;
	frameDelay = bottleNS::ANIMATION_DELAY;
	startFrame = bottleNS::START_THROW_FRAME;       // first frame of ship animation
	endFrame = bottleNS::END_THROW_FRAME;         // last frame of ship animation
	currentFrame = startFrame;
	visible = false; 
	throwTimer = 0;
}

//=============================================================================
// update
// typically called once per frame
//=============================================================================
void Bottle::update(Entity *hero, float frameTime)
{
	if(!visible)
		return;
	
	if(throwTimer == 0) {
		throwTimer = bottleNS::SWING_TIME;
	}

	if((throwTimer -= frameTime) <= 0) {
		visible = false;
		active = false;
		throwTimer = 0;
	}


	velocity.x = hero->getVelocity().x;
	velocity.x = hero->getVelocity().y;

	spriteData.x += velocity.x * frameTime;
	spriteData.y += velocity.y * frameTime;
	velocity = D3DXVECTOR2(0, 0);
}

//=============================================================================
// swing
// Handle sword swinging
//=============================================================================
void Bottle::toss(Entity *hero, D3DXVECTOR2 vec)
{

	setFrames(bottleNS::START_THROW_FRAME,bottleNS::END_THROW_FRAME);
	setCurrentFrame(bottleNS::START_THROW_FRAME);



	
	visible = true;
	active = true;
}