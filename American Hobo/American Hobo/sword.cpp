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
	visible = false; 
	swingTimer = 0;
}

//=============================================================================
// update
// typically called once per frame
//=============================================================================
void Sword::update(Entity *hero, float frameTime)
{
	if(!visible)
		return;
	
	if(swingTimer == 0) {
		swingTimer = swordNS::SWING_TIME;
	}

	if((swingTimer -= frameTime) <= 0) {
		visible = false;
		active = false;
		swingTimer = 0;
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
void Sword::swing(Entity *hero, DIRECTION dir)
{
	if(dir == RIGHT) {
		setX(hero->getCenterX() - spriteData.width / 2 + swordNS::SWING_RANGE);
		setY(hero->getCenterY() - spriteData.height / 2);
	} else if(dir == LEFT) {
		setX(hero->getCenterX() - spriteData.width / 2 - swordNS::SWING_RANGE);
		setY(hero->getCenterY() - spriteData.height / 2);
	} else if(dir == UP) {
		setX(hero->getCenterX() - spriteData.width / 2);
		setY(hero->getCenterY() - spriteData.height / 2 - swordNS::SWING_RANGE);
	} else if(dir == DOWN) {
		setX(hero->getCenterX() - spriteData.width / 2);
		setY(hero->getCenterY() - spriteData.height / 2 + swordNS::SWING_RANGE);
	}

	if(dir == UP) {
		setFrames(swordNS::SWING_UP,swordNS::SWING_UP);
		setCurrentFrame(swordNS::SWING_UP);
	} else if(dir == RIGHT) {
		setFrames(swordNS::SWING_RIGHT, swordNS::SWING_RIGHT);
		setCurrentFrame(swordNS::SWING_RIGHT);
	} else if(dir == DOWN) {
		setFrames(swordNS::SWING_DOWN, swordNS::SWING_DOWN);
		setCurrentFrame(swordNS::SWING_DOWN);
	} else if(dir == LEFT) {
		setFrames(swordNS::SWING_LEFT, swordNS::SWING_LEFT);
		setCurrentFrame(swordNS::SWING_LEFT);
	}
	
	visible = true;
	active = true;
}