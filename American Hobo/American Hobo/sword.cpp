#include "sword.h"

//=============================================================================
// default constructor
//=============================================================================
Sword::Sword() : Entity()
{
	active = false;                                 // torpedo starts inactive
	spriteData.width = swordNS::WIDTH;     // size of 1 image
	spriteData.height = swordNS::HEIGHT;
	spriteData.rect.bottom = swordNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = swordNS::WIDTH;
	cols = swordNS::TEXTURE_COLS;
	frameDelay = swordNS::ANIMATION_DELAY;
	startFrame = swordNS::START_FRAME;       // first frame of ship animation
	endFrame = swordNS::END_FRAME;         // last frame of ship animation
	currentFrame = startFrame;
	radius = swordNS::COLLISION_RADIUS;  // for circular collision
	visible = true; //change to false later
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// update
// typically called once per frame
//=============================================================================
void Sword::update(float frameTime)
{
	if (!visible)
		return;
}

//=============================================================================
// swing
// Handle sword swinging
//=============================================================================
void Sword::swing(Entity *hero)
{
	spriteData.x = hero->getCenterX() - spriteData.width / 2;
	spriteData.y = hero->getCenterY() - spriteData.height / 2;
	visible = true;                         // make sword visible
	active = true;                          // enable collisions
	//Check collision
	//Set back to inactive and invisible
}