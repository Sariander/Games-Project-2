#ifndef _MILKSHOT_H              // Prevent multiple definitions if this 
#define _MILKSHOT_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace milkShotNS
{
    const int   WIDTH = 32;             // image width
    const int   HEIGHT = 32 ;           // image height
    const int   COLLISION_RADIUS = 4;   // for circular collision
    const float SPEED = 200;            // pixels per second
    const float MASS = 300.0f;          // mass
    const int   TEXTURE_COLS = 0;       // texture has 8 columns
    const int   START_FRAME = 0;       // starts at frame 40
    const int   END_FRAME = 0;         // animation frames 40,41,42,43
    const float ANIMATION_DELAY = 0.1f; // time between frames
	const float FIRE_DELAY = 2.0f;
}

class MilkShot : public Entity           // inherits from Entity class
{
private:
    float fireTimer;

public:
    MilkShot();
	bool ready;
    void update(float frameTime);
    float getMass()    const {return milkShotNS::MASS;}

    void fire(Entity *ship, float rotOffset);   
};
#endif