#include "milkShot.h"

//=============================================================================
// default constructor
//=============================================================================
MilkShot::MilkShot() : Entity()
{
    active = false;                                 // torpedo starts inactive
    spriteData.width        = milkShotNS::WIDTH;     // size of 1 image
    spriteData.height       = milkShotNS::HEIGHT;
    spriteData.rect.bottom  = milkShotNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right   = milkShotNS::WIDTH;
    cols            = milkShotNS::TEXTURE_COLS;
    frameDelay      = milkShotNS::ANIMATION_DELAY;
    startFrame      = milkShotNS::START_FRAME;       // first frame of ship animation
    endFrame        = milkShotNS::END_FRAME;         // last frame of ship animation
    currentFrame    = startFrame;
    radius          = milkShotNS::COLLISION_RADIUS;  // for circular collision
    visible         = false;
    mass = milkShotNS::MASS;
    collisionType = entityNS::CIRCLE;
	ready = true;
	fireTimer = 0;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void MilkShot::update(float frameTime)
{
    if (!visible)
        return;

	if(getScale() < .75)
		setScale(getScale() + .01);

    Image::update(frameTime);

    spriteData.x += frameTime * velocity.x;     // move along X 
    spriteData.y += frameTime * velocity.y;     // move along Y

    if (spriteData.x > GAME_WIDTH) {              // if off right screen edge
		visible = false;
		ready = true;
		active = false;
	}
    else if (spriteData.x < -milkShotNS::WIDTH) {  // else if off left screen edge
		visible = false;
		ready = true;
		active = false;
	}
    if (spriteData.y > GAME_HEIGHT) {             // if off bottom screen edge
		visible = false;
		ready = true;
		active = false;
	}
    else if (spriteData.y < -milkShotNS::HEIGHT) { // else if off top screen edge
        visible = false;
		ready = true;
		active = false;
	}
}

//=============================================================================
// fire
// Fires a torpedo from ship
//=============================================================================
void MilkShot::fire(Entity *ship, float rotOffset)
{
    velocity.x = (float)cos(ship->getRadians()+3*PI/2 + rotOffset*PI/180) * milkShotNS::SPEED;
    velocity.y = (float)sin(ship->getRadians()+3*PI/2 + rotOffset*PI/180) * milkShotNS::SPEED;
    spriteData.x = ship->getCenterX() - spriteData.width/2 + velocity.x/10;
    spriteData.y = ship->getCenterY() - spriteData.height/2 + velocity.y/10;
    visible = true;                         // make torpedo visible
    active = true;                          // enable collisions
	ready = false;

	setScale(.4);
}