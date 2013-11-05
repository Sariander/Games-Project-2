// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Version 1.0

#ifndef _TORPEDO_H              // Prevent multiple definitions if this 
#define _TORPEDO_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace torpedoNS
{
    const int   WIDTH = 32;             // image width
    const int   HEIGHT = 32 ;           // image height
    const int   COLLISION_RADIUS = 4;   // for circular collision
    const float SPEED = 300;            // pixels per second
    const float MASS = 300.0f;          // mass
    const float FIRE_DELAY = 1.5f;      // 4 seconds between torpedo firing
    const int   TEXTURE_COLS = 0;       // texture has 8 columns
    const int   START_FRAME = 0;       // starts at frame 40
    const int   END_FRAME = 0;         // animation frames 40,41,42,43
    const float ANIMATION_DELAY = 0.1f; // time between frames
}

class Torpedo : public Entity           // inherits from Entity class
{
private:
    float   fireTimer;

public:
    // constructor
    Torpedo();
	bool ready;

    // inherited member functions
    void update(float frameTime);
    float getMass()    const {return torpedoNS::MASS;}
    // new member functions
    void fire(Entity *ship);                // fire torpedo from ship
};
#endif
