// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// torpedo.cpp v1.0

#include "torpedo.h"

//=============================================================================
// default constructor
//=============================================================================
Torpedo::Torpedo() : Entity()
{
    active = false;                                 // torpedo starts inactive
    spriteData.width        = torpedoNS::WIDTH;     // size of 1 image
    spriteData.height       = torpedoNS::HEIGHT;
    spriteData.rect.bottom  = torpedoNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right   = torpedoNS::WIDTH;
    cols            = torpedoNS::TEXTURE_COLS;
    frameDelay       = torpedoNS::ANIMATION_DELAY;
    startFrame      = torpedoNS::START_FRAME;       // first frame of ship animation
    endFrame        = torpedoNS::END_FRAME;         // last frame of ship animation
    currentFrame    = startFrame;
    radius          = torpedoNS::COLLISION_RADIUS;  // for circular collision
    visible         = false;
    mass = torpedoNS::MASS;
    collisionType = entityNS::CIRCLE;
	ready = true;
	fireTimer = 0;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Torpedo::update(float frameTime)
{
    if (!visible)
        return;

    Image::update(frameTime);

    spriteData.x += frameTime * velocity.x;     // move along X 
    spriteData.y += frameTime * velocity.y;     // move along Y

    if (spriteData.x > GAME_WIDTH) {              // if off right screen edge
		visible = false;
		ready = true;
		active = false;
	}
    else if (spriteData.x < -torpedoNS::WIDTH) {  // else if off left screen edge
		visible = false;
		ready = true;
		active = false;
	}
    if (spriteData.y > GAME_HEIGHT) {             // if off bottom screen edge
		visible = false;
		ready = true;
		active = false;
	}
    else if (spriteData.y < -torpedoNS::HEIGHT) { // else if off top screen edge
        visible = false;
		ready = true;
		active = false;
	}
}

//=============================================================================
// fire
// Fires a torpedo from ship
//=============================================================================
void Torpedo::fire(Entity *ship)
{
    velocity.x = (float)cos(ship->getRadians()+PI/2) * torpedoNS::SPEED;
    velocity.y = (float)sin(ship->getRadians()+PI/2) * torpedoNS::SPEED;
    spriteData.x = ship->getCenterX() - spriteData.width/2;
    spriteData.y = ship->getCenterY() - spriteData.height/2;
    visible = true;                         // make torpedo visible
    active = true;                          // enable collisions
	ready = false;
}

