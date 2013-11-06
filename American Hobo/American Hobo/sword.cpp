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
	visible = true; //change to false later
}

//=============================================================================
// update
// typically called once per frame
//=============================================================================
void Sword::update(float frameTime)
{
	if (!visible)
		return;
	if (input->isKeyDown(HERO_LEFT_KEY))
	{
		velocity.x = -swordNS::SPEED;
	}
	if (input->isKeyDown(HERO_RIGHT_KEY))
	{
		velocity.x = swordNS::SPEED;
	}
	if (input->isKeyDown(HERO_UP_KEY))
	{
		velocity.y = -swordNS::SPEED;
	}
	if (input->isKeyDown(HERO_DOWN_KEY))
	{
		velocity.y = swordNS::SPEED;
	}
	spriteData.x += velocity.x * frameTime;
	spriteData.y += velocity.y * frameTime;
	velocity = D3DXVECTOR2(0, 0);
}

//=============================================================================
// swing
// Handle sword swinging
//=============================================================================
void Sword::swing(Entity *hero)
{
	setX(hero->getCenterX() - spriteData.width / 2);
	setY(hero->getCenterY() - spriteData.height / 2);
	visible = true;                         // make sword visible
	active = true;                          // enable collisions
	//Check collision
	//Set back to inactive and invisible
}