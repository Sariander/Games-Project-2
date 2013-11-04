// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// ship.h v1.0

#ifndef _SHIP_H                 // Prevent multiple definitions if this 
#define _SHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "torpedo.h"
#include "textDX.h"

namespace shipNS
{
    const int   WIDTH = 32;                 // image width (each frame)
    const int   HEIGHT = 32;                // image height
    const int   X = GAME_WIDTH/2 - WIDTH/2; // location on screen
    const int   Y = GAME_HEIGHT/6 - HEIGHT;
    const float ROTATION_RATE = (float)PI; // radians per second
    const float SPEED = 100;                // 100 pixels per second
    enum DIRECTION {NONE, LEFT, RIGHT};     // rotation direction
    const int   TEXTURE_COLS = 0;           // texture has 8 columns
    const float TORPEDO_DAMAGE = 10;        // amount of damage caused by torpedo
    const float SHIP_DAMAGE = 10;           // damage caused by collision with another ship

	const int NUM_SHOTS = 60;
	const float COLOR_WAIT = .10f;
}

// inherits from Entity class
class Ship : public Entity
{
private:
	float fireTimer;
	float fireWait;
	float theta;
	float colorTimer;
	COLOR_ARGB filter;
	

public:
    // constructor
    Ship();

    // inherited member functions
    virtual void draw(float frameTime);
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);

    // update ship position and angle
    void update(float frameTime);

	void fire();
	Torpedo shotBuffer[shipNS::NUM_SHOTS];
	Image healthHUD;
	Image scoreHUD;

	int score;
    // damage ship with WEAPON
    void damage(WEAPON);
    
    // move ship out of collision

    // ship explodes
    void explode();

    // ship is repaired
    void repair();

	float getHealth() {return health;}
};
#endif

