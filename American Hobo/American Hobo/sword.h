#ifndef _SWORD_H              // Prevent multiple definitions if this 
#define _SWORD_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace swordNS
{
	const int   WIDTH = 10;             // image width
	const int   HEIGHT = 60;           // image height
	const float FIRE_DELAY = 1.5f;      // 4 seconds between torpedo firing
	const int   TEXTURE_COLS = 0;       // texture has 8 columns
	const int   START_FRAME = 0;       // starts at frame 40
	const int   END_FRAME = 0;         // animation frames 40,41,42,43
	const float ANIMATION_DELAY = 0.1f; // time between frames
	const int	SPEED = 100;
}

class Sword : public Entity           // inherits from Entity class
{
private:

public:
	// constructor
	Sword();

	void update(float frameTime);
	void swing(Entity *hero);                // fire torpedo from ship
};
#endif