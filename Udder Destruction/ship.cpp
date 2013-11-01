// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// ship.cpp v1.0

#include "ship.h"
#include "turret.h"
#include "cybovine.h"
#include <sstream>
using namespace turretNS;
using namespace cybovineNS;

//=============================================================================
// default constructor
//=============================================================================
Ship::Ship() : Entity()
{
    spriteData.width = shipNS::WIDTH;           // size of Ship1
    spriteData.height = shipNS::HEIGHT;
    spriteData.x = shipNS::X;                   // location on screen
    spriteData.y = shipNS::Y;
    spriteData.rect.bottom = shipNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = shipNS::WIDTH;
    radius = shipNS::WIDTH/2.0;
    collisionType = entityNS::CIRCLE;

	fireWait = 0.4f;
	fireTimer = 0.0f;
	theta = 180;
	filter = SETCOLOR_ARGB(0,0,0,0);
	colorTimer = 0.0f;

}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Ship::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	score = 00;
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Ship::draw(float frameTime)
{
	if(colorTimer > 0)
		colorTimer -= frameTime;
	for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
		shotBuffer[i].draw();
	}
	if(colorTimer <= 0.0f) {
		filter = SETCOLOR_ARGB(0, 0, 0, 0);
		Image::draw(spriteData, filter);
	} else {
		filter = SETCOLOR_ARGB(255, 255, 30, 30);
		Image::draw(spriteData, filter);
	}
    
	healthHUD.draw();
	scoreHUD.draw();

}


//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Ship::update(float frameTime)
{
	for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
		shotBuffer[i].update(frameTime); //move to ship update
	}

    Entity::update(frameTime);

	if (health > 0)
	{
		if(input->isKeyDown(SHIP_LEFT_KEY))            // if move right
		{
			theta += 0.5;
			if(theta > 360)
				theta = 0;
		}
		if(input->isKeyDown(SHIP_RIGHT_KEY))             // if move left
		{
			theta -= 0.5;
			if(theta < 0)
				theta = 360;
		}

		if(input ->isKeyDown(SHIP2_FORWARD_KEY))
		{
			fire();
		}
	}

	float conRad = PI/180;

	float newX = 300*cos(theta*conRad - PI/2) + GAME_WIDTH/2; //300 is rotation radius
	float newY = 300*sin(theta*conRad - PI/2) + GAME_HEIGHT/2;

	setCenterX(newX);
	setCenterY(newY);
	setDegrees(theta);

	fireTimer -= frameTime;
}

//================================================================================
// fire
//================================================================================
void Ship::fire() {
	if(fireTimer <= 0.0f) {
		for(int i = 0; i < shipNS::NUM_SHOTS; i++) {
			if(shotBuffer[i].ready) {
				shotBuffer[i].fire(this);
				fireTimer = fireWait;
				break;
			}
		}
	}
	return;
}

//=============================================================================
// damage
//=============================================================================
void Ship::damage(WEAPON weapon)
{
    switch(weapon)
    {
	case MILK:
		health -= turretNS::MILK_DAMAGE;
		colorTimer = cybovineNS::COLOR_WAIT;
		break;
	case EYE:
		health -= cybovineNS::EYE_DAMAGE;
		colorTimer = cybovineNS::COLOR_WAIT;
		break;
    }
    if (health <= 0)
        explode();
	
	healthHUD.setCurrentFrame(healthHUD.getCurrentFrame() + 1);
}

//=============================================================================
// explode
//=============================================================================
void Ship::explode()
{
    //audio->playCue(EXPLODE);
    active = false;
	visible = false;
    health = 0;
	healthHUD.setVisible(false);
}

//=============================================================================
// repair
//=============================================================================
void Ship::repair()
{
    active = true;
    health = FULL_HEALTH;
    visible = true;
	healthHUD.setVisible(true);
}

